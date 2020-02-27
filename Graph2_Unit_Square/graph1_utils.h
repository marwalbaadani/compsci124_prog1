#ifndef GRAPH1_UTILS
#define GRAPH1_UTILS

#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>

using namespace std;

float rando();

typedef struct node
{
    int rank;
    float x_val;
    float y_val;
    node *parent;
    node()
    {
        rank = 0;
        parent = this;
        x_val = rando();
        y_val = rando();
    }
} node;

tuple<float, node *, node *> *kruskal(tuple<float, node *, node *> tuple_t[], int n);

node *find(node *x);

node *link(node *x, node *y);

void unite(node *x, node *y);

#endif