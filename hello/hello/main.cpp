//
//  main.cpp
//  hello
//
//  Created by Marwa Albaadani on 2/20/20.
//  Copyright © 2020 Marwa Albaadani. All rights reserved.
//

// my first program in C++
#include <iostream>
#include <cstdlib>
#include <random>
#include <iterator>
#include <list>
#include <string>
#include <tuple>

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

   //list<tuple<int, int, int>> tab;

    tuple<int, double, string> result(7, 9.8, "text");



    // std::tuple<int, int, int> i3tuple(){
    //     return std::tuple<int, int, int>{1, 1, 1}};
    // for (int n = 0; n < 10; ++n)
    // {
    //     // Use dis to transform the random unsigned int generated by gen into a
    //     // double in [1, 2). Each call to dis(gen) generates a new random double
    //     std::cout << dis(gen) << ' ';
    // }
    // std::cout << '\n';
    tuple< int, int, float> bruh[n*n];
    

//it = myvector.begin();
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // std::cout << dis(gen) << ' ';
           // x[i][j] = dis(gen);

             //bruh.insert (it, 1,2,3.00);
            
     //       bruh[count] =(1, 2, dis(gen));
            cout << "Element at x[" << i
                 << "][" << j << "]: ";
            cout << x[i][j] << "\n";
            count++;
        }
    }
}