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
// using namespace std::chrono;

int main()
{
    // auto start = high_resolution_clock::now();

    // declare variables
    int n;

    // take user input
    cout << "Please enter a number of nodes: ";
    cin >> n;

    // create n vertices 
    node *vertices[n];
    for (int i = 0; i < n; i++)
    {
        node *p = new node();
        vertices[i] = p;
    }

    // create list of tuples to represent the graph
    tuple<float, node *, node *> *tuple_t = new tuple<float, node *, node *>[(n * (n - 1)) / 2];

    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            tuple_t[count] = make_tuple(i, vertices[i], vertices[j]);
            count++;
        }
    }

    // implement kruskal's algorithm
    kruskal(tuple_t, n);

    // clear memory in the heap
    delete[] tuple_t;
    for (int i = 0; i < n; i++)
    {
        delete vertices[i];
    }

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() / 1000000 << endl; 
}