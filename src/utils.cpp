/*=======================================
 utils.hpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Useful function implementations.
========================================*/


#include <algorithm>
#include <iostream>
#include <vector>

#include "../include/utils.hpp"

using std::vector;


bool get_int_in_vector(int i, vector<int> vec) {
    return std::find(vec.begin(), vec.end(), i) != vec.end();
}


void print_2d_vector(vector< vector<int> > vec, bool color) {
    for ( int x = 0; x < vec.size(); x++ ) {
        for ( int y = 0; y < vec.back().size(); y++ ) {
            if ( color ) {
                int c = vec[x][y];
                if ( c == 1 ) {
                    std::cout << "\033[32m\u25A0\033[0m ";
                } else if ( c == 2 ) {
                    std::cout << "\033[38;5;172m\u25A0\033[0m ";
                } else if ( c == 3 ) {
                    std::cout << "\033[37m\u25A0\033[0m ";
                } else if ( c == 4 ) {
                    std::cout << "\033[34m\u25A0\033[0m ";
                } else if ( c == 5 ) {
                    std::cout << "\033[31m\u25A0\033[0m ";
                } else if ( c == 6 ) {
                    std::cout << "\033[33m\u25A0\033[0m ";
                }
            } else {
                std::cout << vec[x][y] << " ";
            }
        }
        std::cout << std::endl;
    }
}