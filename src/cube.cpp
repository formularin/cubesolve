/*=======================================
 cube.cpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 Implementations for the `Cube` class.
========================================*/


#include <string>
#include <vector>

#include "../include/cube.hpp"


using std::vector;


Cube::Cube() {
    // Constructor for Cube class.
    // Starts in solved state.

    // Fill all stickers to make solved cube.
    for (int color = 1; color <= 6; color++) {
        vector< vector<int> > new_face(3, vector<int>(3, color));
        faces.push_back(new_face);
    }
}