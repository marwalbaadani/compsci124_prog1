#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>

using namespace std;

typedef struct node
{
    int rank = 0;
    node *parent = this;
} node;

node *find(node *x)
{
    if (x != x->parent)
    {
        x->parent = find(x->parent);
    }
    return x->parent;
}

node *link(node *x, node *y)
{
    if (x->rank > y->rank)
        y->parent = x; //yay
    if (x->rank == y->rank)
        y->rank++;
    x->parent = y;
    return y;
}

void unite(node *x, node *y)
{
    link(find(x), find(y));
    return;
}

tuple<float, node *, node *> *kruskal(tuple<float, node *, node *> tuple_t[], int n)
{
    node *vertices[n];
    //n-1 list
    tuple<float, node *, node *> *edges[n - 1];

    sort(tuple_t, tuple_t + (n * n));
    for (int i = 0; i < (n * (n - 1)) / 2; i++)
    {
        cout << " yo(" << get<0>(tuple_t[i]) << ", " << get<1>(tuple_t[i]) << ", " << get<2>(tuple_t[i]) << ") \n";
    }
    int mst = 0;

    for (int k = 0; k < (n * (n - 1)) / 2; k++)
    {
        cout << "hey " << get<1>(tuple_t[k]) << "\n";
        if (find(get<1>(tuple_t[k])) != find(get<2>(tuple_t[k])))
        {
            // add to edges
            // edges[mst] = &tuple_t[k];
            cout << "aye \n";
            mst++;
            //unite(get<1>(tuple_t[k]), get<2>(tuple_t[k]));
        }
    }
    cout << "mst val: " << mst << "\n";
    return *edges;
}

int main()
{
    // declare variables
    int n;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // take user input
    cout << "Please enter a number of nodes: ";
    cin >> n;
    float x[n][n];

    node *vertices[n];
    // create list of tuples representation of graphs
    tuple<float, node *, node *> tuple_t[(n * (n - 1)) / 2];
    cout << "come on i see it";
    for (int i = 0; i < n; i++)
    {
        // cout << "open your purse";
        node *p = new node();
        vertices[i] = p;
    }
    // cout << "so I can get a slushie";
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = dis(gen);
            cout << rando << std::endl;
            tuple_t[count] = make_tuple(rando, vertices[i], vertices[j]);
            // cout << "bitch u got a doller";
            // cout << " (" << get<0>(tuple_t[count]) << ", " << (vertices[i]->parent) << ", " << (vertices[j]->parent) << ") \n";
            count++;
        }
    }

    cout << "weewee";

    kruskal(tuple_t, 10);
    // for (int i = 0; i < 45; i++)
    // {
    //     cout << " (" << get<0>(tuple_t2[i]) << ", " << get<1>(tuple_t2[i]) << ", " << get<2>(tuple_t2[i]) << ") \n";
    // }
}

// node vertex;
// vertex.v = count;
// vertex.parent = &vertex;
// x[i][j] = rando;
// x[j][i] = rando
// for (int i = 0; i < n; ++i)
// {
//     cout << "[ ";
//     for (int j = 0; j < n; j++)
//     {
//         cout << " " << x[i][j] << " ";
//     }
//     cout << " ] \n";
// }

// cout << " la la separator \n";
// set<tuple<float, int, int>> first;

//  cout << " (" << get<0>(tuple_t[count]) << ", " << get<1>(tuple_t[count]) << ", " << get<2>(tuple_t[count]) << ") \n";

// for (int i = 0; i < n * n; i++)
// {
//     cout << " (" << get<0>(tuple_t[i]) << ", " << get<1>(tuple_t[i]) << ", " << get<2>(tuple_t[i]) << ") \n";
// }