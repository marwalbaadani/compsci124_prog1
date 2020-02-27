#include <iostream>
#include <cstdlib>
// #include <chrono>
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
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

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
    // tuple<float, node *, node *> *tuple_t = new tuple<float, node *, node *>[(n * (n - 1)) / 2];

    vector<tuple<float, node *, node *>> tuple_t;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = dis(gen);
            if (n > 5000 && rando > (n^(-1/3))){
            tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }

        }
    }

    // implement kruskal's algorithm
    
    kruskal(tuple_t, n);

    // clear memory in the heap
    // delete[] tuple_t;
    tuple_t.clear();
    for (int i = 0; i < n; i++)
    {
        delete vertices[i];
    }

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() / 1000000 << endl;
}