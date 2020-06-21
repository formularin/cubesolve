/*=======================================
 op_op.hpp:                     lol-cubes
 last modified:           Sun, 06/21/2020
 
 Header file for Old Pochman edges and
 corners algorithm implementation.
========================================*/


#include <string>

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
    {{1, 2}, {'L', 'F'}},
    {{1, 3}, {'I', 'C'}},
    {{1, 5}, {'J', 'P'}},
    {{1, 6}, {'K', 'U'}},
    {{2, 3}, {'E', 'D'}},
    {{2, 4}, {'H', 'R'}},
    {{2, 6}, {'G', 'X'}},
    {{3, 4}, {'A', 'Q'}},
    {{3, 5}, {'B', 'M'}},
    {{4, 5}, {'T', 'N'}},
    {{4, 6}, {'S', 'W'}},
    {{5, 6}, {'O', 'V'}}
};
static std::map<char, char> edge_sticker_pairs = {
    {'L', 'F'},
    {'I', 'C'},
    {'J', 'P'},
    {'K', 'U'},
    {'E', 'D'},
    {'H', 'R'},
    {'G', 'X'},
    {'A', 'Q'},
    {'B', 'M'},
    {'T', 'N'},
    {'S', 'W'},
    {'O', 'V'},
    {'F', 'L'},
    {'C', 'I'},
    {'P', 'J'},
    {'U', 'K'},
    {'D', 'E'},
    {'R', 'H'},
    {'X', 'G'},
    {'Q', 'A'},
    {'M', 'B'},
    {'N', 'T'},
    {'W', 'S'},
    {'V', 'O'}
};


char get_edge_sticker_from_coords(int f, int r, int c, Cube cube);
vector<int> get_coords_from_sticker(char sticker);
std::string solve_op_op(Cube cube);