/*=======================================
 moves.hpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 Classes pertaining to moves and move
 notation. (Uses WCA notation)
========================================*/


#include <string>
#include <vector>
#include <map>

using std::vector;


std::map<std::string, int> move_coords = {
    { "L", 0 },
    { "R", 1 },
    { "D", 0 },
    { "U", 1 },
    { "F", 0 },
    { "B", 1 }
};


class Move {
    int rotations;
    std::string direction;  // C or CC
    std::string axis;

    // Arbitrarily decided value that specifies
    // what pieces are being moved.
    int coord;

    public:
    std::string move;  // String representation.
    Move(std::string move_string);
};


class MoveString {
    vector<Move> moves;
    vector<std::string> comments;

    public:
    // Print moves in readable format.
    std::string create_reconstruction();
    void add_comment(int index);
    MoveString(vector<Move> moves_string);
};