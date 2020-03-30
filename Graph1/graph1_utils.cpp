#include "graph1_utils.h"

#include <math.h>
#include <iterator>
#include <random>
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);

float distance(node *vertex_1, node *vertex_2, int dimension)
{

    if (dimension == 1) // 2d - unit square
    {
        return (sqrt(pow((vertex_2->x_val - vertex_1->x_val), 2) + pow(vertex_2->y_val - vertex_1->y_val, 2)));
    }
    else if (dimension == 2) // 3d - unit cube
    {
        return (sqrt(pow((vertex_2->x_val - vertex_1->x_val), 2) + pow(vertex_2->y_val - vertex_1->y_val, 2) + pow(vertex_2->z_val - vertex_1->z_val, 2)));
    }
    else if (dimension == 3) // 4d - unit hypercube
    {
        return (sqrt(pow((vertex_2->x_val - vertex_1->x_val), 2) + pow(vertex_2->y_val - vertex_1->y_val, 2) + pow(vertex_2->z_val - vertex_1->z_val, 2) + pow(vertex_2->w_val - vertex_1->w_val, 2)));
    }
    else
    {

        return dis(gen);
    }
}

tuple<float, node *, node *> *kruskal(vector<tuple<float, node *, node *>> tuple_t, int n, unsigned long long int edges)
{
    tuple<float, node *, node *> *mstEdges[n - 1];

    // sort our list of tuples
    sort(tuple_t.begin(), tuple_t.end());

    int mst = 0;

    for (int k = 0; k < edges; k++)
    {
        if ((find(get<1>(tuple_t[k])) != find(get<2>(tuple_t[k]))))
        {
            // add to edges djkdfsl
            mstEdges[mst] = &tuple_t[k];
            mst++;
            unite(get<1>(tuple_t[k]), get<2>(tuple_t[k]));
        }
    }
    // cout << "mst val: " << mst << "\n";

    long double avg = 0;
    for (int i = 0; i < mst; i++)
    {
        avg += get<0>(*mstEdges[i]);
    }

    cout << "avg: " << avg << endl;

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
        return x;
    }
    if (x->rank == y->rank)
    {
        y->rank++;
    }
    x->parent = y;
    return y;
}

void unite(node *x, node *y)
{
    link(find(x), find(y));
    return;
}
