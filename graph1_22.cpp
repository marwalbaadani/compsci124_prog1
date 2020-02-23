#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>

using namespace std;

struct Node
{
    int v;
    struct Node *next;
};

int main()
{
    // random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // declare variables
    int n;

    // take user input
    cout << "Please enter a number of nodes: ";
    cin >> n;
    float x[n][n];

    // create list of tuples representation of graphs
    tuple<float, int, int> tuple_t[n * n];

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            // std::cout << dis(gen) << ' ';
            float rando = dis(gen);

            x[i][j] = rando;
            x[j][i] = rando;
            tuple_t[count] = make_tuple(x[i][j], i, j);
            cout << " (" << get<0>(tuple_t[count]) << ", " << get<1>(tuple_t[count]) << ", " << get<2>(tuple_t[count]) << ") \n";

            count++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "[ ";
        for (int j = 0; j < n; j++)
        {
            cout << " " << x[i][j] << " ";
        }
        cout << " ] \n";
    }

    cout << " la la separator \n";
    sort(tuple_t, tuple_t + (n * n));

    // set<tuple<float, int, int>> first;

    for (int i = 0; i < n * n; i++)
    {
        cout << " (" << get<0>(tuple_t[i]) << ", " << get<1>(tuple_t[i]) << ", " << get<2>(tuple_t[i]) << ") \n";
    }
}

// set kruskal(matrix float[][])
// {
// }