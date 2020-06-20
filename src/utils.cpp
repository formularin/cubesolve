/*=======================================
 utils.hpp:                     lol-cubes
 last modified:           Sat, 06/20/2020
 
 Useful function implementations.
========================================*/


#include <algorithm>
#include <iostream>
#include <vector>

#include "../include/utils.hpp"

using std::vector;


bool get_char_in_vector(char c, vector<char> vec) {
    return std::find(vec.begin(), vec.end(), c) != vec.end();
}


bool get_int_in_vector(int i, vector<int> vec) {
    return std::find(vec.begin(), vec.end(), i) != vec.end();
}


bool get_string_in_vector(std::string string, vector<std::string> vec) {
    return std::find(vec.begin(), vec.end(), string) != vec.end();
}


bool get_vector_in_vector(vector<int> v, vector< vector<int> > vec) {
    return std::find(vec.begin(), vec.end(), v) != vec.end();
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


void print_int_vector(vector<int> vec) {
    for ( int v : vec ) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}


vector< vector<int> > rotate_face(vector< vector<int> > face, std::string direction) {
    // Best explained by example:
    // 5 5 5  C   1 1 5
    // 1 1 6  ->  1 1 5
    // 1 1 6      6 6 5
    // Direction is "C" or "CC". As of right now, only takes 3x3 vectors.

    vector< vector<int> > rotated_face(3, vector<int>(3));

    if ( direction == "C" ) {
        // Corners
        rotated_face[0][0] = face[2][0];
        rotated_face[0][2] = face[0][0];
        rotated_face[2][2] = face[0][2];
        rotated_face[2][0] = face[2][2];

        // Edges
        rotated_face[0][1] = face[1][0];
        rotated_face[1][0] = face[2][1];
        rotated_face[1][2] = face[0][1];
        rotated_face[2][1] = face[1][2];
    } else if ( direction == "CC" ) {
        // Corners
        rotated_face[0][0] = face[0][2];
        rotated_face[0][2] = face[2][2];
        rotated_face[2][2] = face[2][0];
        rotated_face[2][0] = face[0][0];

        // Edges
        rotated_face[0][1] = face[1][2];
        rotated_face[1][0] = face[0][1];
        rotated_face[1][2] = face[2][1];
        rotated_face[2][1] = face[1][0];
    }

    // Center
    rotated_face[1][1] = face[1][1];

    return rotated_face;
}