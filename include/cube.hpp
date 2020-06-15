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

// Coordinate pairs in `faces` for stickers of edge pieces.
static vector< vector< vector<int> > > adjacent_edge_stickers = {
    { {0, 0, 1}, {2, 2, 1} },
    { {0, 1, 0}, {1, 1, 2} },
    { {0, 1, 2}, {4, 1, 0} },
    { {0, 2, 1}, {5, 0, 1} },
    { {1, 0, 1}, {2, 1, 0} },
    { {1, 1, 0}, {3, 1, 2} },
    { {1, 2, 1}, {5, 1, 0} },
    { {2, 0, 1}, {3, 0, 1} },
    { {2, 1, 2}, {4, 0, 1} },
    { {3, 1, 0}, {4, 1, 2} },
    { {3, 2, 1}, {5, 2, 1} },
    { {4, 2, 1}, {5, 1, 2} }
};

class Cube {
    // Which direction each face is affected in when moved on each axis.
    static char direction(int face_index, int axis);
    static std::string choose_move(vector<std::string> current_moves,
                                   vector< vector<std::string> > axes,
                                   vector< vector<std::string> > sides);

    public:
    Cube();
    void execute(std::string moves);
    void scramble();  // Execute random moves.
    void print();
    void turn(Move move);
    // Each face is a 3x3 vector of ints.
    // Face's index in list corresponds to its center color.
    vector< vector< vector<int> > > faces;
};

#endif