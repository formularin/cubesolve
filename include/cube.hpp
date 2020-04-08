/*=======================================
 cube.hpp:                      lol-cubes
 last modified:               Wed, Apr 08
 
 The `Cube` class, which represents a
 Rubik's Cube. Everything is organized in
 2 dimensions, concerning only faces and
 stickers.
========================================*/


#include <string>
#include <vector>
#include <map>

#include "moves.hpp"

using std::vector;


#ifndef CUBE_H
#define CUBE_H

// ints correspond to potential colors for each sticker.
#define enum colors { green, orange, white, blue, red, yellow };

class Cube {
    // Each face is a 3x3 vector of ints.
    // Face's index in list corresponds to its center color.
    vector< vector< vector<int> > > faces;

    // Which direction each face is affected in when moved on each axis.
    static char direction(int face_index, int axis);

    public:
    Cube();
    void execute(std::string moves);
    void scramble();  // Execute random moves.
    void print();
    void turn(Move move);
};

#endif