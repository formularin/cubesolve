/*=======================================
 cube.hpp:                      lol-cubes
 last modified:               Tue, Mar 31
 
 The `Cube` class, which represents a
 Rubik's Cube. Everything is organized in
 2 dimensions, concerning only faces and
 stickers.
========================================*/


#include <string>
#include <vector>

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

    void turn(Move move);

    // Solving functions
    void solve_op_op();

    public:
    Cube();
    void solve(std::string method);
    void execute(std::string moves);
    void scramble();
    void print();
};

#endif