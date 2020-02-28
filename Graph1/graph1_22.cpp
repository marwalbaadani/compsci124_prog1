#include <iostream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>
#include <math.h>
#include "graph1_utils.h"

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();

    // declare variables
    int n;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // take user input
    cout << "Please enter a number of nodes: ";
    cin >> n;

    // create n vertices
    cout << "pre vertice creation \n";
    node *vertices[n];
    for (int i = 0; i < n; i++)
    {
        node *p = new node();
        vertices[i] = p;
    }
    cout << "post vertice creation \n";

    // create list of tuples to represent the graph
    // tuple<float, node *, node *> *tuple_t = new tuple<float, node *, node *>[(n * (n - 1)) / 2];

    cout << "pre vector creation \n";
    vector<tuple<float, node *, node *>> tuple_t;

    cout << "post vector creation \n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = dis(gen);
            if (n < 10000) {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            } else if (n >= 200000 && rando < 1/(log(n^5)))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);                
            } else if (n >= 50000 && rando < 1/(log(n^3)))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);                
            } else if (n >= 10000 && rando < 1/(log(n^2)))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            } else {
                continue;
            }

        }
    }

    cout << "post vector fill \n";

    // implement kruskal's algorithm

    unsigned long long int edges = tuple_t.size();
    
    kruskal(tuple_t, n, edges);

    // clear memory in the heap
    // delete[] tuple_t;
    tuple_t.clear();
    for (int i = 0; i < n; i++)
    {
        delete vertices[i];
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() / 1000000 << endl;
}