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
#include "graph1_utils.h"

using namespace std;
using namespace std::chrono;

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
    cout << "pre vertice creation \n";
    node *vertices[n];
    for (int i = 0; i < n; i++)
    {
        node *p = new node(dimension, dis(gen), dis(gen), dis(gen), dis(gen));
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
            float rando = distance(vertices[i], vertices[j], dimension);

            if (n < 10000)
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }
            else if (n < 200000 || (n >= 10000 && rando < 1 / (log(n ^ 10))))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }
            else if (n < 50000 || (n >= 10000 && rando < 1 / (log(n ^ 3))))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }
            else if (n < 10000 || (n >= 10000 && rando < 1 / (log(n ^ 2))))
            {
                tuple_t.emplace_back(rando, vertices[i], vertices[j]);
            }
            else
            {
                continue;
            }
        }
    }

    cout << "post vector fill \n";

    // implement kruskal's algorithm

    unsigned long long int edges = tuple_t.size();

    tuple<float, node *, node *> *mst = kruskal(tuple_t, n, edges);

    // clear memory in the heap
    // delete[] tuple_t;
    tuple_t.clear();
    for (int i = 0; i < n; i++)
    {
        delete vertices[i];
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "It took me " << elapsed.count() << " microseconds." << std::endl;

    float average = 0;
    for (int i = 0; i < n - 1; i++)
    {
        average += get<0>(mst[i]);
    }
    average /= (n - 1);
    cout << "Average edge weight for your " << dimension + 1 << "D graph of " << n << " nodes: " << average
         << "\n";
}