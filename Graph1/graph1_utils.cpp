#include "graph1_utils.h"

vector<float> *kruskal(vector<float> tuple_t[], int n)
{
    // tuple<float, node *, node *> *mstEdges[n - 1];

    // sort our list of tuples
    // sort(tuple_t, tuple_t + ((n * (n - 1)) / 2));
    sort(tuple_t, tuple_t + ((n * (n - 1)) / 2));

    // int mst = 0;

    // for (int k = 0; k < (n * (n - 1)) / 2; k++)
    // {
    //     if (find(get<1>(tuple_t[k])) != find(get<2>(tuple_t[k])))
    //     {
    //         // add to edges
    //         mstEdges[mst] = &tuple_t[k];
    //         mst++;
    //         unite(get<1>(tuple_t[k]), get<2>(tuple_t[k]));
    //     }
    // }
    // cout << "mst val: " << mst << "\n";
    // return *mstEdges;
    return tuple_t;
}

// node *find(node *x)
// {
//     if (x != x->parent)
//     {
//         x->parent = find(x->parent);
//     }
//     return x->parent;
// };

// node *link(node *x, node *y)
// {
//     if (x->rank > y->rank)
//     {
//         y->parent = x;
//         return x;
//     }
//     if (x->rank == y->rank)
//     {
//         y->rank++;
//     }
//     x->parent = y;
//     return y;
// }

// void unite(node *x, node *y)
// {
//     link(find(x), find(y));
//     return;
// }
