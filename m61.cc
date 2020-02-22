#define M61_DISABLE 1
#include "m61.hh"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cinttypes>
#include <cassert>
#include <algorithm>

metadata *PREV_MALLOC = nullptr;
const char HEADER[8] = "ohmagod";
const char TRAILER[8] = "plswork";

// initialize 5 counters to catch all cases >= 20% (100% / 5)
hh_counter hh_counters[5] = {
    {0, "", -1},
    {0, "", -1},
    {0, "", -1},
    {0, "", -1},
    {0, "", -1},
};
long long total_hh_dec = 0;

m61_statistics memory = {
    0, 0, 0, 0, 0, 0, (unsigned long)-1, 0};

// increment_hh(sz, file, line)
//     Increments the heavy hitter counters
void increment_hh(size_t sz, const char *file, long line)
{
    for (int i = 0; i < 5; ++i)
    {
        if (line == hh_counters[i].line)
        {
            // If counter found, increment and return
            hh_counters[i].bytes += sz;
            return;
        }
        if (hh_counters[i].bytes <= 0)
        {
            // If not found, assign and return
            hh_counters[i].line = line;
            hh_counters[i].file = file;
            hh_counters[i].bytes = sz;
            return;
        }
    }
    // If no counter available, decrement all counters
    for (int i = 0; i < 5; ++i)
    {
        hh_counters[i].bytes -= sz;
    }
    total_hh_dec += sz;
}
/// m61_malloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
///    The memory is not initialized. If `sz == 0`, then m61_malloc must
///    return a unique, newly-allocated pointer value. The allocation
///    request was at location `file`:`line`.

void *m61_malloc(size_t sz, const char *file, long line)
{
    (void)file, (void)line; // avoid uninitialized variable warnings

    // check that sz is not too big
    if (sz > (unsigned int)-1)
    {
        memory.nfail++;
        memory.fail_size += sz;
        return nullptr;
    }

    // allocate enough memory for payload, metadata, header and footer
    metadata *meta_ptr = (metadata *)((uintptr_t)base_malloc(sz + sizeof(metadata) + sizeof(HEADER) + sizeof(TRAILER)) + sizeof(HEADER));

    // check if allocation succeeded
    if (!meta_ptr)
    {
        memory.nfail++;
        memory.fail_size += sz;
        return nullptr;
    }

    *meta_ptr = {
        sz,
        PREV_MALLOC,
        nullptr,
        file,
        line,
        true,
    };

    if (PREV_MALLOC)
    {
        PREV_MALLOC->next = meta_ptr;
    }
    PREV_MALLOC = meta_ptr;

    memcpy((void *)((uintptr_t)meta_ptr - sizeof(HEADER)), (void *)HEADER, sizeof(HEADER));
    memcpy((void *)((uintptr_t)(meta_ptr + 1) + sz), (void *)TRAILER, sizeof(TRAILER));

    increment_hh(sz, file, line);

    memory.heap_min = std::min((uintptr_t)(meta_ptr + 1), memory.heap_min);
    memory.heap_max = std::max((uintptr_t)(meta_ptr + 1) + sz, memory.heap_max);
    memory.nactive++;
    memory.active_size += sz;
    memory.ntotal++;
    memory.total_size += sz;

    // Return pointer to object payload
    return (meta_ptr + 1);
}

void checkObjectBoundaries(metadata *ptr)
{
    if (!PREV_MALLOC)
    {
        return;
    }
    metadata *curr = PREV_MALLOC;
    do
    {
        if ((uintptr_t)curr < (uintptr_t)ptr && (uintptr_t)curr + curr->size > (uintptr_t)ptr)
        {
            fprintf(stderr, "  %s:%li: %p is %zu bytes inside a %zu byte region allocated here\n", curr->file, curr->line, ptr + 1, (uintptr_t)ptr - (uintptr_t)curr, curr->size);
            return;
        }
    } while (!(curr = curr->prev));
}

/// m61_free(ptr, file, line)
///    Free the memory space pointed to by `ptr`, which must have been
///    returned by a previous call to m61_malloc. If `ptr == NULL`,
///    does nothing. The free was called at location `file`:`line`.

void m61_free(void *ptr, const char *file, long line)
{
    (void)file, (void)line; // avoid uninitialized variable warnings

    if (!ptr)
    {
        return;
    }

    metadata *meta_ptr = (metadata *)ptr - 1;

    // Check that pointer is within heap
    if ((uintptr_t)ptr < memory.heap_min ||
        (uintptr_t)ptr > memory.heap_max)
    {

        fprintf(stderr, "MEMORY BUG: %s:%li: invalid free of pointer %p, not in heap\n", file, line, ptr);
        abort();
    }
    // Check if memory has ever been allocated
    if ((uintptr_t)meta_ptr % 8 != 0 ||
        (unsigned int)-1 < meta_ptr->size ||
        memcmp((void *)((uintptr_t)meta_ptr - sizeof(HEADER)), HEADER, sizeof(HEADER)) != 0 ||
        (meta_ptr->prev && meta_ptr->prev->next != meta_ptr))
    {
        fprintf(stderr, "MEMORY BUG: %s:%li: invalid free of pointer %p, not allocated\n", file, line, ptr);
        checkObjectBoundaries(meta_ptr);
        abort();
    }
    // Check that pointer is active (no double-frees)
    if (!meta_ptr->active ||
        (meta_ptr->prev && meta_ptr->prev->next != meta_ptr))
    {
        fprintf(stderr, "MEMORY BUG: %s:%li: invalid free of pointer %p, double free\n", file, line, ptr);
        abort();
    }
    // Check that no wild writes occurred over object's lifespan
    if (memcmp((void *)((uintptr_t)(meta_ptr + 1) + meta_ptr->size), TRAILER, sizeof(TRAILER)) != 0)
    {
        fprintf(stderr, "MEMORY BUG: %s:%li: detected wild write during free of pointer %p\n", file, line, ptr);
        abort();
    }

    // noop variable used to throw away assignment in case next/prev do not exist
    metadata *noop;
    (!meta_ptr->next ? noop : meta_ptr->next->prev) = meta_ptr->prev;
    (!meta_ptr->prev ? noop : meta_ptr->prev->next) = meta_ptr->next;
    PREV_MALLOC = !meta_ptr->next ? meta_ptr->prev : PREV_MALLOC;

    meta_ptr->active = false;
    memory.nactive--;
    memory.active_size -= meta_ptr->size;

    base_free((void *)((uintptr_t)meta_ptr - sizeof(HEADER)));
}

/// m61_calloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. If `sz == 0`,
///    then must return a unique, newly-allocated pointer value. Returned
///    memory should be initialized to zero. The allocation request was at
///    location `file`:`line`.

// Checks if multiplication overflows, returns false if it does
bool multIsUnsafe(size_t a, size_t b)
{
    size_t res = a * b;
    return a && !(res / a == b);
}

void *m61_calloc(size_t nmemb, size_t sz, const char *file, long line)
{
    if (sz == 0 || nmemb == 0)
    {
        return memset(m61_malloc(0, file, line), 0, 0);
    }

    // Check if safe size inputs (no overflow)
    if (multIsUnsafe(nmemb, sz))
    {
        memory.nfail++;
        memory.fail_size += nmemb * sz;
        return nullptr;
    }

    void *ptr = m61_malloc(nmemb * sz, file, line);
    if (ptr)
    {
        memset(ptr, 0, nmemb * sz);
    }
    return ptr;
}

/// m61_get_statistics(stats)
///    Store the current memory statistics in `*stats`.

void m61_get_statistics(m61_statistics *stats)
{
    // Stub: set all statistics to enormous numbers
    memcpy(stats, &memory, sizeof(m61_statistics));
}

/// m61_print_statistics()
///    Print the current memory statistics.

void m61_print_statistics()
{
    m61_statistics stats;
    m61_get_statistics(&stats);

    printf("alloc count: active %10llu   total %10llu   fail %10llu\n",
           stats.nactive, stats.ntotal, stats.nfail);
    printf("alloc size:  active %10llu   total %10llu   fail %10llu\n",
           stats.active_size, stats.total_size, stats.fail_size);
}

/// m61_print_leak_report()
///    Print a report of all currently-active allocated blocks of dynamic
///    memory.

void m61_print_leak_report()
{
    metadata *curr = PREV_MALLOC;
    if (!curr)
    {
        return;
    }
    do
    {
        printf("LEAK CHECK: %s:%li: allocated object %p with size %zu\n", curr->file, curr->line, curr + 1, curr->size);
    } while ((curr = curr->prev));
}

/// m61_print_heavy_hitter_report()
///    Print a report of heavily-used allocation locations.

int comp_hh(const void *ptr1, const void *ptr2)
{
    return ((hh_counter *)ptr1)->bytes < ((hh_counter *)ptr2)->bytes ? 1 : -1;
};

void m61_print_heavy_hitter_report()
{
    // sort counters by # bytes allocated
    qsort(hh_counters, 5, sizeof(hh_counter), comp_hh);
    for (int i = 0; i < 5; ++i)
    {
        if (hh_counters[i].line != -1 && (float)(hh_counters[i].bytes) / (float)memory.total_size * 100 > 5)
            printf("HEAVY HITTER: %s:%li: %lli bytes (~%.2f%%)\n", hh_counters[i].file, hh_counters[i].line, hh_counters[i].bytes, (float)(hh_counters[i].bytes + total_hh_dec) / (float)memory.total_size * 100);
        hh_counters[i].bytes = -1;
    }
}

// Realloc implementation
void *realloc(void *ptr, size_t sz, const char *file, long line)
{
    // avoid uninitialized warning
    metadata *meta_ptr = nullptr;
    if (ptr)
    {
        meta_ptr = ((metadata *)ptr - 1);
        m61_free(meta_ptr, file, line);
    }
    if (sz != 0)
    {
        void *newptr = m61_malloc(sz, file, line);
        memcpy(newptr, ptr, meta_ptr ? std::min(sz, meta_ptr->size) : sz);
        return newptr;
    }

    return nullptr;
}