/*=======================================
 op_op.cpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Implements the Old Pochmand algorithm
 for both edges and corners.
========================================*/


#include <map>
#include <vector>
#include <string>

#include "../../include/methods/op_op.hpp"
#include "../../include/cube.hpp"
#include "../../include/moves.hpp"

using std::vector;


// Assigns each edge and corner a letter unique to their respective sets
// of edges and corners. Corners are lowercase, edges are uppercase.
// Centers are labeled 'z' because they aren't touched.
static vector< vector< vector<char> > > lettering_scheme = {
    // Green
    {{'i', 'I', 'j'},
     {'L', 'z', 'J'},
     {'l', 'K', 'k'}},
    // Orange
    {{'e', 'E', 'f'},
     {'H', 'z', 'F'},
     {'h', 'G', 'g'}},
    // White
    {{'a', 'A', 'b'},
     {'D', 'z', 'B'},
     {'d', 'C', 'c'}},
    // Blue
    {{'q', 'Q', 'r'},
     {'T', 'z', 'R'},
     {'t', 'S', 's'}},
    // Red
    {{'m', 'M', 'n'},
     {'P', 'z', 'N'},
     {'p', 'O', 'o'}},
    // Yellow
    {{'u', 'U', 'v'},
     {'X', 'z', 'V'},
     {'x', 'W', 'w'}}
};
// Algorithms to move a selected edge across from the buffer spot
// without disturbing the corners next to it.
static std::map<char, std::string> edge_algorithms = {
    { 'A', "R2 U' R2" },
    // 'B' is the buffer.
    { 'C', "R2 U R2" },
    { 'D', ""},
    { 'E', "L U' F U" },
    { 'F', "U' F U" },
    { 'G', "L' U' F U" },
    { 'H', "U B' U'" },
    { 'I', "R F' L' R'" },
    { 'J', "U2 R U2" },
    { 'K', "R F L' R'" },
    { 'L', "L'" },
    // 'M' is the other sticker of the buffer..
    { 'N', "U B U'" },
    { 'O', "D' R F L' R'" },
    { 'P', "U' F' U" },
    { 'Q', "R' B L R" },
    { 'R', "L" },
    { 'S', "R' B' L R" },
    { 'T', "U2 R' U2" },
    { 'U', "D' L2" },
    { 'V', "D2 L2" },
    { 'W', "D L2" },
    { 'X', "L2" }
};


MoveString solve_op_op(Cube cube) {
    // Returns MoveString containing solution and explanatory comments.
    // Cube enters solved state.
}