#include "graph1_utils.h"
using namespace std;

vector<tuple<float, node, node>> kruskal(vector<tuple<float, node, node>> tuple_t, unsigned long long int n)
{
    vector<tuple<float, node, node>> mstEdges;

    // sort our list of tuples
    //sort(tuple_t, tuple_t + ((n * (n - 1)) / 2));
    sort(tuple_t.begin(), tuple_t.end());
    int mst = 0;

    for (int k = 0; k < (n * (n - 1)) / 2; k++)
    {
        if (find(get<1>(tuple_t[k])) != find(get<2>(tuple_t[k])))
        {
            // add to edges
            mstEdges.emplace_back(&tuple_t[k]);
            mst++;
            unite(get<1>(tuple_t[k]), get<2>(tuple_t[k]));
        }
    }
    cout << "mst val: " << mst << "\n";
    return mstEdges;
}

node find(node x)
{
    if (x.parent != x.parent)
    {
        x.parent = find(x);
    }
    return x.parent;
};

node *link(node x, node y)
{
    if (x.rank > y.rank)
    {
        y.parent = x.parent;
        return x.parent;
    }
    if (x.rank == y.rank)
    {
        y.rank++;
    }
    x.parent = y.parent;
    return y.parent;
}

void unite(node x, node y)
{
    link(*find(x), *find(y));
    return;
}
