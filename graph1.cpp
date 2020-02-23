// my first program in C++
#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>
#include <list>

using namespace std;

// typedef std::tuple<int, int, int> i3tuple;

int main()
{

    int n;
    cout << "Please enter an integer value: ";
    cin >> n;
    float x[n][n];
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(0.0, 1.0);

    tuple<int, int, float> tuple_t[n * n];

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // std::cout << dis(gen) << ' ';
            if (i == j)
            {
                continue;
            }
            else
            {
                x[i][j] = dis(gen);
                // assign value t
                tuple_t[count] = make_tuple(i, j, x[i][j]);
            }
            count++;
        }
    }
}
