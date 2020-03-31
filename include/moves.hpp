/*=======================================
 moves.hpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Classes pertaining to moves and move
 notation. (Uses WCA standards)
========================================*/


#include <string>
#include <vector>
#include <map>

using std::vector;

#ifndef MOVES_H
#define MOVES_H


// Index of row or col of 3x3 face vector that contains stickers that
// would change as a result of each move.
std::map<std::string, int> move_coords = {
    { "L", 2 },
    { "R", 0 },
    { "D", 2 },
    { "U", 0 },
    { "B", 2 },
    { "F", 0 }
};


class Move {
    public:
    int rotations;
    // C or CC
    // Perspectives:
    // U or D -> from above
    // R or L -> from the right
    // F or B -> from the front
    std::string direction;

    // Axes:
    // x (U and D) -> 0
    // y (R and L) -> 1
    // z (F and B) -> 2
    int axis;

    // Index of row or col of 3x3 face vector that
    // contains stickers that are changing.
    int coord;

    std::string move;  // String representation.
    Move(std::string move_string);
};


class MoveString {
    vector<Move> moves;
    vector<std::string> comments;

    public:
    std::string create_reconstruction();
    void add_comment(int index);
    MoveString(vector<Move> moves_string);
};

#endif