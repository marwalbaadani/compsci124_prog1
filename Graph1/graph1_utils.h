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

vector<float> *kruskal(vector<float> tuple_t[], int n);

node *find(node *x);

node *link(node *x, node *y);

void unite(node *x, node *y);

#endif