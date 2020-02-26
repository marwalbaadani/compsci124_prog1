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
    unsigned long long int n;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // take user input
    cout << "Please enter a number of nodes: ";
    cin >> n;

    // create n vertices
    // node *vertices[n];
    // recheck for better way to store nodes

    cout << "pre array creation \n";
    vector<node> vertices;

    for (int i = 0; i < n; i++)
    {
        // node *p = new (nothrow) node();
        vertices.push_back(node());
    }

    cout << "post array creation \n";

    // create list of tuples to represent the graph
    unsigned long long int blue = (n * (n - 1)) / 2;
    cout << blue << "\n";

    vector<tuple<float, node, node>> tuple_t;

    cout << "pre array";
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = dis(gen);

            tuple_t.push_back(make_tuple(rando, vertices[i], vertices[j]));
            // tuple_t[count] = ;
            // count++;t
        }
    }

    // implement kruskal's algorithm
    cout << "pre kruskal \n";
    kruskal(tuple_t, n);

    // clear memory in the heap
    // delete[] tuple_t;
    // for (int i = 0; i < n; i++)
    // {
    //     delete vertices[i];
    // }

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count() / 1000000 << endl;
}
