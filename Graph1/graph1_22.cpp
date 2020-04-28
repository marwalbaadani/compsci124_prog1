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
#include <ctime>

using namespace std;
#include "graph1_utils.h"

using namespace std;
using namespace std::chrono;
tuple<float, node *, node *> *mst;
int main(int argc, char **argv)
{
    auto start = steady_clock::now();

    // declare variables
    int flag = atoi(argv[1]);
    int n = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // take user input

    // create n vertices
    // cout << "pre vertice creation \n";
    node *vertices[n];
    for (int i = 0; i < n; i++)
    {
        node *p = new node(dimension, dis(gen), dis(gen), dis(gen), dis(gen));
        vertices[i] = p;
    }
    // cout << "post vertice creation \n";

    // create list of tuples to represent the graph
    // tuple<float, node *, node *> *tuple_t = new tuple<float, node *, node *>[(n * (n - 1)) / 2];

    // cout << "pre vector creation \n";
    vector<tuple<float, node *, node *>> tuple_t;

    // cout << "post vector creation \n";
    float bound = (log2(n ^ 2) / sqrt(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float rando = distance(vertices[i], vertices[j], dimension);

            if (rando < bound)
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }
        }
    }
    // cout << "post vector fill \n";

    // implement kruskal's algorithm

    unsigned long long int edges = tuple_t.size();

    tuple<float, node *, node *> *mst = kruskal(tuple_t, n, edges);
    
    tuple_t.clear();
    for (int i = 0; i < n; i++)
    {
        delete vertices[i];
    }
    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "It took me " << elapsed.count() << " microseconds." << endl;
}

