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


void print_sticker_row(vector<int> stickers) {
    for ( int s : stickers ) {
        if ( s == 1 ) {
            std::cout << "\033[32m\u25A0\033[0m ";
        } else if ( s == 2 ) {
            std::cout << "\033[38;5;172m\u25A0\033[0m ";
        } else if ( s == 3 ) {
            std::cout << "\033[37m\u25A0\033[0m ";
        } else if ( s == 4 ) {
            std::cout << "\033[34m\u25A0\033[0m ";
        } else if ( s == 5 ) {
            std::cout << "\033[31m\u25A0\033[0m ";
        } else if ( s == 6 ) {
            std::cout << "\033[33m\u25A0\033[0m ";
        }
    }
}


vector< vector<int> > rotate_face(vector< vector<int> > face, std::string direction) {
    // Best explained by example:
    // 5 5 5  CC  1 1 5
    // 1 1 6  ->  1 1 5
    // 1 1 6      6 6 5
    // Direction is "C" or "CC"

    vector< vector<int> > rotated_vec(face.back().size(), vector<int>(face.size()));
    for ( int x = 0; x < face.size(); x++ ) {
        for ( int y = 0; y < face[x].size(); y++ ) {
            if ( direction == "CC" ) {
                rotated_vec[face[x].size() - (y + 1)][x] = face[x][y];
            } else if ( direction == "C" ) {
                rotated_vec[y][x] = face[x][y];
            }
        }
    }
    return rotated_vec;
}