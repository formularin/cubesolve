/*=======================================
 op_op.hpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Header file for Old Pochman edges and
 corners algorithm implementation.
========================================*/


#include "../moves.hpp"
#include "../cube.hpp"


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
// Letters of pieces corresponding to colors.
static std::map<vector<int>, vector<int>> edge_stickers_by_color = {
//   Colors     Edges
    {{0, 1}, {'L', 'F'}},
    {{0, 2}, {'I', 'C'}},
    {{0, 4}, {'J', 'P'}},
    {{0, 5}, {'K', 'U'}},
    {{1, 2}, {'E', 'D'}},
    {{1, 3}, {'H', 'R'}},
    {{1, 5}, {'G', 'X'}},
    {{2, 3}, {'A', 'Q'}},
    {{2, 4}, {'B', 'M'}},
    {{3, 4}, {'T', 'N'}},
    {{3, 5}, {'S', 'W'}},
    {{4, 5}, {'O', 'V'}}
};


char get_edge_sticker_from_coords(int f, int r, int c, Cube cube);
vector<int> get_coords_from_sticker(char sticker);
MoveString solve_op_op(Cube cube);