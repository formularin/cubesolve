/*=======================================
 op_op.cpp:                     lol-cubes
 last modified:           Tue, 06/16/2020
 
 Implements the Old Pochman algorithm
 for both edges and corners.
========================================*/


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

#include "../../include/methods/op_op.hpp"
#include "../../include/cube.hpp"
#include "../../include/moves.hpp"
#include "../../include/utils.hpp"

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

    vector<Move> solution_moves;

    // Memorization

    // Edges
    // =========================================

    std::set<char> unsolved_edge_stickers = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'};
    vector<char> edge_memo;
   
    // Check for edge pieces that are already solved.

    vector< vector<int> > checked_sticker_coords;

    // Iterate over all coordinate pairs of stickers
    for ( int face = 0; face < 6; face++ ) {
        for ( int row = 0; row < 3; row++ ) {
            for ( int col = 0; col < 3; col++ ) {

                // Check if sticker is an edge sticker.
                if ( (row == 0 && col != 1) || (row == 1 && col == 1) || (row == 2 && col != 1) ) continue;

                // Check if sticker is not already checked.
                vector<int> current_sticker_coords = {face, row, col};
                if ( get_vector_in_vector(current_sticker_coords, checked_sticker_coords) ) continue;
                
                // Mark both stickers of edge as checked.
                vector<int> adjacent_sticker_coords = adjacent_edge_stickers[current_sticker_coords];
                checked_sticker_coords.push_back(current_sticker_coords);
                checked_sticker_coords.push_back(adjacent_sticker_coords);

                // Check if sticker has same color as center of face.
                if ( cube.faces[face][1][1] != cube.faces[face][row][col] ) continue;
                
                // Check if adjacent sticker has same color as center of face.
                if (    cube.faces[adjacent_sticker_coords[0]][1][1]
                     != cube.faces[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]) continue;
                
                // If it passed all those tests, both stickers can be removed from the unsolved list.
                unsolved_edge_stickers.erase(lettering_scheme[face][row][col]);
                unsolved_edge_stickers.erase(
                    lettering_scheme[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]);
            }
        }
    }

    return MoveString({Move("R")});
}