/*=======================================
 cube.cpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Implementations for the `Cube` class.
========================================*/


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../include/cube.hpp"
#include "../include/moves.hpp"
#include "../include/utils.hpp"

using std::vector;


Cube::Cube() {
    // Constructor for Cube class.
    // Starts in solved state.

    // Fill all stickers to make solved cube.
    for (int color = 1; color <= 6; color++) {
        vector< vector<int> > new_face(3, vector<int>(3, color));
        faces.push_back(new_face);
    }
}


// Private functions
// ----------------


void Cube::turn(Move move) {
    // Performs one move on the cube. Changes stickers accordingly.

    vector<int> untouched;
    for ( int i = 0; i < 2; i++ ) {
        untouched.push_back(2 * move.axis + move.coord);
    }

    // Vector of each sticker that is changing in each face.
    // Only 4 faces change, and 3 stickers per face change per move.
    // Will always be in order of movement because of arrangement of
    // faces in faces member.
    vector< vector<int> > changing_stickers(4, vector<int>(3));
    for ( int f = 0; f < 6; f++ ) {
        if ( !get_int_in_vector(f, untouched) ) {
            vector< vector<int> > face = faces[f];
            if ( move.axis != 1 ) {
                // Moving stickers are in a row.
                changing_stickers.push_back(face[move.coord]);
            } else {
                // Moving stickers are in a column.
                vector<int> face_changing_stickers(3);
                for ( int i = 0; i < 3; i++ ) {
                    face_changing_stickers.push_back(face[i][move.coord]);
                }
                changing_stickers.push_back(face_changing_stickers);
            }
        }
    }

    // Get list of all changed stickers.
    vector< vector<int> > changed_stickers(4, vector<int>(4));
    if ( move.direction == "C" ) {
        changed_stickers[0] = changing_stickers[3];
        for ( int i = 1; i < 4; i++ ) {
            changed_stickers[i] = changing_stickers[i - 1];
        }
    } else if ( move.direction == "CC" ) {
        changed_stickers[3] = changing_stickers[0];
        for ( int i = 0; i < 3; i++ ) {
            changed_stickers[i] = changing_stickers[i + 1];
        }
    }

    // Apply changed stickers to faces.
    for ( int f = 0; f < 6; f++ ) {
        if ( !get_int_in_vector(f, untouched) ) {
            if ( move.axis != 1 ) {
                // Moving stickers are in a row.
                faces[f][move.coord] = changed_stickers[f];
            } else {
                // Moving stickers are in a column.
                for ( int i = 0; i < 3; i++ ) {
                    faces[f][i][move.coord] = changed_stickers[f][i];
                }
            }
        }
    }
}


// Public functions
// ----------------


void Cube::print() {
    // Outputs readable rendering of cube sticker faces to console.

    std::string face_colors[6] = {"green", "orange", "white",
                                  "blue", "red", "yellow"};
    for ( int f = 0; f < 6; f++ ) {
        std::cout << face_colors[f] << std::endl;
        print_2d_vector(faces[f]);
    }
}


void Cube::scramble(std::string moves) {
    // Performs inputted moves on cube.
    // Moves should be in WCA notation and separated by spaces.
    // Input string "none" executes a random scramble.

    Move move = Move("R");
    turn(move);
}