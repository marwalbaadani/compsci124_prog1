// We are currently stuck with segementation fault coming from line 61's find(get<1>(tuple_t[k]).
// We are currently trying to make sure that the correct weight is attached to the tuples

#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>
#include "graph1_utils.h"

using namespace std;

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

    node *vertices[n];

    for (int i = 0; i < n; i++)
    {
        node *p = new node();
        vertices[i] = p;
        // cout << vertices[i]->parent << "  " << vertices[i]->rank << "\n";
    }

    // create list of tuples representation of graphs
    tuple<float, node *, node *> tuple_t[(n * (n - 1)) / 2];

    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = dis(gen);
            // cout << rando << std::endl;
            tuple_t[count] = make_tuple(rando, vertices[i], vertices[j]);
            // cout << "bitch u got a doller";
            // cout << " (" << get<0>(tuple_t[count]) << ", " << (vertices[i]->parent) << ", " << (vertices[j]->parent) << ") \n";
            count++;
        }
    }
    cout << "pre-kruskal\n";
    kruskal(tuple_t, n);
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