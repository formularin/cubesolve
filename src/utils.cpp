/*=======================================
 utils.hpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 Useful function implementations.
========================================*/


#include <algorithm>
#include <iostream>
#include <vector>

#include "../include/utils.hpp"

using std::vector;


bool get_int_in_vector(int i, vector<int> vec) {
    return std::find(vec.begin(), vec.end(), i) != vec.end;
}


void print_2d_vector(vector< vector<int> > vec) {
    for ( int x = 0; x < vec.size(); x++ ) {
        for ( int y = 0; x < vec.back().size(); y++ ) {
            std::cout << vec[x][y] << " ";
        }
        std::cout << std::endl;
    }
}