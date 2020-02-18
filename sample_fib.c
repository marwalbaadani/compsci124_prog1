#include <stdio.h>
#include <time.h>
void *memcpy(void *dest, const void *src, size_t n);

int fib(int n);
int fib2(int n);
int fib3(int n);

int main()
{
    clock_t start_t, end_t;
    clock_t start_t2, end_t2;
    clock_t start_t3, end_t3;

    // find the nth number in the fibonacci sequence
    int n = 0;
    printf("Give me a number: ");
    scanf("%d", &n);

    // recursive method
    start_t = clock();
    fib(n);
    end_t = clock();
    double total_t = ((double)((end_t - start_t))) / CLOCKS_PER_SEC;
    // double total_t = (long) / CLOCKS_PER_SEC;
    printf("Total time taken by recursive fib: %f\n", total_t);

    for (int i = 0; i < 200; i++)
    {
        printf("%d: %d \n", i, fib(i));
    }

    // matrix method
    start_t2 = clock();
    fib2(n);
    end_t2 = clock();
    double total_t2 = ((double)((end_t2 - start_t2))) / CLOCKS_PER_SEC;
    printf("Total time taken by matrix fib: %f\n", total_t2);

    // iterative method
    start_t3 = clock();
    fib3(n);
    end_t3 = clock();
    double total_t3 = ((double)((end_t3 - start_t3))) / CLOCKS_PER_SEC;
    printf("Total time taken by iterative fib: %f\n", total_t3);
}

int fib(int n)
{
    if (n <= 1)
        return n % 65536;
    return (fib(n - 1) + fib(n - 2)) % 65536;
}

int fib2(int n)
{
    int c[2][2] = {{0, 1}, {1, 1}};
    int d[2][2];
    int f[2];
    if (n <= 1)
    {
        return n % 65536;
    }
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            // multiply the matrix by itself n times
            d[0][0] = (c[0][0] * 0 + c[0][1] * 1) % 65536;
            d[0][1] = (c[0][0] * 1 + c[0][1] * 1) % 65536;
            d[1][0] = (c[1][0] * 0 + c[1][1] * 1) % 65536;
            d[1][1] = (c[1][0] * 1 + c[1][1] * 1) % 65536;
            memcpy(c, d, sizeof d);
        }

        // multiply the nth matrix by f0 and f1
        // printf("d: %d and d1: %d \n", d[1][1], d[0][0]);
        f[0] = (d[0][0] * 0 + d[0][1] * 1) % 65536;
        f[1] = (d[1][0] * 0 + d[1][1] * 1) % 65536;

        // printf("f0: %d and f1: %d \n", f[0], f[1]);
        // printf("fib2: %d", f[0]);
        return f[0];
    }
    return 0;
}

int fib3(int n)
{
    // find the nth fibonacci number
    int fn[2] = {0, 1};

    int counter = 0;
    while (counter < n - 1)
    {
        int temp = fn[1];
        fn[1] = (fn[0] + fn[1]) % 65536;
        fn[0] = temp;
        counter++;
    }

    return fn[1];
}