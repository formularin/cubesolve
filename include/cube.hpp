/*=======================================
 cube.hpp:                      lol-cubes
 last modified:               Mon, Mar 30
 
 The `Cube` class, which represents a
 Rubik's Cube. Everything is organized in
 2 dimensions, concerning only faces and
 stickers.
========================================*/


#include <string>
#include <vector>

// ints correspond to potential colors for each sticker.
#define white 0
#define yellow 1
#define green 2
#define blue 3
#define red 4
#define orange 5


using std::vector;


class Cube {
    // Each face is a 3x3 vector of ints.
    // Face's index in list corresponds to its center color.
    vector< vector< vector<int> > > faces;

    void turn(std::string move);

    // Solving functions
    void solve_op_op();

    public:
    Cube();
    void solve(std::string method);
    void scramble(std::string moves);
};