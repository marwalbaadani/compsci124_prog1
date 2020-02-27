#include "graph1_utils.h"
#include <iostream>

tuple<float, node *, node *> *kruskal(tuple<float, node *, node *> tuple_t[], int n)
{
    tuple<float, node *, node *> *mstEdges[n - 1];

    // sort our list of tuples
    sort(tuple_t, tuple_t + ((n * (n - 1)) / 2));

    int mst = 0;

    for (int k = 0; k < (n * (n - 1)) / 2; k++)
    {
        if (find(get<1>(tuple_t[k])) != find(get<2>(tuple_t[k])))
        {
            // add to edges
            mstEdges[mst] = &tuple_t[k];
            mst++;
            unite(get<1>(tuple_t[k]), get<2>(tuple_t[k]));
        }
    }
    cout << "mst val: " << mst << "\n";
    return *mstEdges;
}

node *find(node *x)
{
    if (x != x->parent)
    {
        x->parent = find(x->parent);
    }
    return x->parent;
};

node *link(node *x, node *y)
{
    if (x->rank > y->rank)
    {
        y->parent = x;
        std::cout << "x-val: " << y->x_val << " y-val: " << y->y_val << std::endl;

        return x;
    }
    if (x->rank == y->rank)
    {
        y->rank++;
    }
    x->parent = y;
    return y;
}

float rando()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

void unite(node *x, node *y)
{
    link(find(x), find(y));
    return;
}
