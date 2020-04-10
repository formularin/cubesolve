/*=======================================
 op_op.cpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Implements the Old Pochmand algorithm
 for both edges and corners.
========================================*/


#include <iostream>
#include <map>
#include <vector>
#include <string>

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


char get_adjacent_sticker(char sticker) {
    // Returns the sticker on the same edge as the sticker passed as an argument.

    for ( vector< vector<int> > edge : adjacent_edge_stickers ) {
        vector<char> edge_stickers;
        for ( vector<int> sticker_coords : edge ) {
            edge_stickers.push_back(
                lettering_scheme[sticker_coords[0]]
                                [sticker_coords[1]]
                                [sticker_coords[2]]);
        }
        for ( int s = 0; s < 2; s++ ) {
            if ( edge_stickers[s] == sticker ) {
                return edge_stickers[1 - s];
            }
        }
    }
    return 'z';
}


MoveString solve_op_op(Cube cube) {
    // Returns MoveString containing solution and explanatory comments.
    // Cube enters solved state.

    vector<Move> solution_moves;

    // Memorization

    // Edges
    vector<char> solved_edge_stickers;
    vector< vector<char> > edge_cycles;
   
    // Check for pieces that are already solved.
    for ( vector< vector<int> > edge : adjacent_edge_stickers ) {
        bool edge_solved = true;
        for ( int s = 0; s < 2; s++ ) {
            if ( !(cube.faces[edge[s][0]][edge[s][1]][edge[s][2]]
                == cube.faces[edge[s][0]][1][1]) ) {
                edge_solved = false;
            }
        }
        // Did not continue, so both the stickers are on the correct
        // face, therefore the edge is solved.
        if ( edge_solved ) {
            for ( int s = 0; s < 2; s++ ) {
                solved_edge_stickers.push_back(
                    lettering_scheme[edge[s][0]][edge[s][1]][edge[s][2]]);
            }
        }
    }

    return MoveString({Move("R")});
}