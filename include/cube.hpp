/*=======================================
 cube.hpp:                      lol-cubes
 last modified:           Tue, 06/16/2020
 
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
// {face, row, col}
static std::map< vector<int>, vector<int> > adjacent_edge_stickers = {
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
    { {4, 2, 1}, {5, 1, 2} },
    { {2, 2, 1}, {0, 0, 1} },
    { {1, 1, 2}, {0, 1, 0} },
    { {4, 1, 0}, {0, 1, 2} },
    { {5, 0, 1}, {0, 2, 1} },
    { {2, 1, 0}, {1, 0, 1} },
    { {3, 1, 2}, {1, 1, 0} },
    { {5, 1, 0}, {1, 2, 1} },
    { {3, 0, 1}, {2, 0, 1} },
    { {4, 0, 1}, {2, 1, 2} },
    { {4, 1, 2}, {3, 1, 0} },
    { {5, 2, 1}, {3, 2, 1} },
    { {5, 1, 2}, {4, 2, 1} }
};
// Coordinate pairs in `faces` for stickers of corner pieces.
// {face, row, col}
static std::map< vector<int>, vector< vector<int> > > adjacent_corner_stickers = {
    { {0, 0, 0}, {{2, 2, 0}, {1, 0, 2}} },
    { {0, 0, 2}, {{2, 2, 2}, {4, 0, 0}} },
    { {0, 2, 0}, {{1, 2, 2}, {5, 0, 0}} },
    { {0, 2, 2}, {{4, 2, 0}, {5, 0, 2}} },
    { {1, 0, 0}, {{2, 0, 0}, {3, 0, 2}} },
    { {1, 0, 2}, {{0, 0, 0}, {2, 2, 0}} },
    { {1, 2, 0}, {{5, 2, 0}, {3, 2, 2}} },
    { {1, 2, 2}, {{0, 2, 0}, {5, 0, 0}} },
    { {2, 0, 0}, {{1, 0, 0}, {3, 0, 2}} },
    { {2, 0, 2}, {{4, 0, 2}, {3, 0, 0}} },
    { {2, 2, 0}, {{0, 0, 0}, {1, 0, 2}} },
    { {2, 2, 2}, {{0, 0, 2}, {4, 0, 0}} },
    { {3, 0, 0}, {{2, 0, 2}, {4, 0, 2}} },
    { {3, 0, 2}, {{1, 0, 0}, {2, 0, 0}} },
    { {3, 2, 0}, {{4, 2, 2}, {5, 2, 2}} },
    { {3, 2, 2}, {{1, 2, 0}, {5, 2, 0}} },
    { {4, 0, 0}, {{0, 0, 0}, {2, 2, 2}} },
    { {4, 0, 2}, {{3, 0, 0}, {2, 0, 2}} },
    { {4, 2, 0}, {{0, 2, 2}, {5, 0, 2}} },
    { {4, 2, 2}, {{3, 2, 0}, {5, 2, 2}} },
    { {5, 0, 0}, {{0, 2, 0}, {1, 2, 2}} },
    { {5, 0, 2}, {{0, 2, 2}, {4, 2, 0}} },
    { {5, 2, 0}, {{3, 2, 2}, {1, 2, 0}} },
    { {5, 2, 2}, {{4, 2, 2}, {3, 2, 0}} }
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