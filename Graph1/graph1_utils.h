#ifndef GRAPH1_UTILS
#define GRAPH1_UTILS

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

using namespace std;

typedef struct node
{
    int rank;
    node *parent;
    float w_val, x_val, y_val, z_val;

    node(int dim, float x_rand, float y_rand, float z_rand, float w_rand)
    {
        if (dim == 1) // 2d - unit square
        {
            x_val = x_rand;
            y_val = y_rand;
        }
        else if (dim == 2) // 3d - unit cube
        {
            x_val = x_rand;
            y_val = y_rand;
            z_val = z_rand;
        }
        else if (dim == 3) // 4d - unit hypercube
        {
            w_val = w_rand;
            x_val = x_rand;
            y_val = y_rand;
            z_val = z_rand;
        }
        rank = 0;
        parent = this;
    }
} node;

tuple<float, node *, node *> *kruskal(vector<tuple<float, node *, node *>> tuple_t, int n, unsigned long long int edges);

node *find(node *x);

node *link(node *x, node *y);

void unite(node *x, node *y);

float distance(node *vertex_1, node *vertex_2, int dimension);
#endif