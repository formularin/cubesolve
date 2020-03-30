/*=======================================
 cube.hpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 The `Cube` class, which represents a
 Rubik's Cube. Everything is organized in
 2 dimensions, concerning only faces and
 stickers.
========================================*/


#include <string>
#include <vector>

// ints correspond to potential colors for each sticker.
#define white 1
#define yellow 2
#define green 3
#define blue 4
#define red 5
#define orange 6


using std::vector;


class Cube {
    // Each face is a 3x3 vector of ints
    vector< vector<int> > white_side();
    vector< vector<int> > yellow_side();
    vector< vector<int> > green_side();
    vector< vector<int> > blue_side();
    vector< vector<int> > red_side();
    vector< vector<int> > orange_side();

    void change_sticker(int side, int x, int y, int color);

    // Solving functions
    void solve_op_op();  // Old Pochman

    public:
    Cube();
    void solve(std::string method);
    void turn(std::string move);
};