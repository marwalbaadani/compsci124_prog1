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

    tuple<float, int, int> tuple_t[n * n];

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // std::cout << dis(gen) << ' ';
            x[i][j] = dis(gen);
            // assign value t
            tuple_t[count] = make_tuple(x[i][j], i, j);
            cout << " (" << get<0>(tuple_t[count]) << ", " << get<1>(tuple_t[count]) << ", " << get<2>(tuple_t[count]) << ") \n";
            count++;
        }
    }

    cout << " la la separator \n";
    sort(tuple_t, tuple_t + (n * n));

    for (int i = 0; i < n * n; i++)
    {
        cout << " (" << get<0>(tuple_t[i]) << ", " << get<1>(tuple_t[i]) << ", " << get<2>(tuple_t[i]) << ") \n";
        }
}
