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

typedef struct node
{
    int rank;
    node *parent;
    node()
    {
        rank = 0;
        parent = this;
    }
} node;

tuple<float, node *, node *> *kruskal(vector<tuple<float, node *, node *>> tuple_t, int n);

node *find(node *x);

node *link(node *x, node *y);

void unite(node *x, node *y);

#endif