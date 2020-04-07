/*=======================================
 cube.cpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Implementations for the `Cube` class.
========================================*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
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


// static method
char Cube::direction(int face_index, int axis) {
    // Returns whether face with index `face_index` when turned on axis
    // `axis` will have rows or columns affected.
    // Returns 'r' if rows, 'c' if columns.

    switch ( face_index ) {
        // Blue or Green
        case 0:
        case 3:
            switch ( axis ) {
                case 0: return 'r';
                case 1: return 'c';
            }
        // Red or Orange
        case 1:
        case 4:
            switch ( axis ) {
                case 0: return 'r';
                case 2: return 'c';
            }
        // White or Yellow
        case 2:
        case 5:
            switch ( axis ) {
                case 1: return 'c';
                case 2: return 'r';
            }
        default:
            throw 20;
    }
}


void Cube::turn(Move move) {
    // Performs one move on the cube. Changes stickers accordingly.

    // Sides that keep all their stickers.
    vector<int> untouched;
    for ( int i = 0; i < 2; i++ ) {
        untouched.push_back(((i * 3) + 2) - move.axis);
    }

    // Vector of each sticker that is changing in each face.
    // Only 4 faces change, and 3 stickers per face change per move.
    // Will always be in order of movement because of arrangement of
    // faces in faces member.
    vector< vector<int> > changing_stickers;
    for ( int f = 0; f < 6; f++ ) {
        if ( !get_int_in_vector(f, untouched) ) {
            vector< vector<int> > face = faces[f];
            if ( direction(f, move.axis) == 'r' ) {
                // Moving stickers are in a row.
                changing_stickers.push_back(face[move.coord]);
            } else if ( direction(f, move.axis) == 'c' ) {
                // Moving stickers are in a column.
                vector<int> face_changing_stickers;
                for ( int i = 0; i < 3; i++ ) {
                    face_changing_stickers.push_back(face[i][move.coord]);
                }
                changing_stickers.push_back(face_changing_stickers);
            }
        }
    }

    // Get list of all changed stickers.
    vector< vector<int> > changed_stickers(4, vector<int>(3));
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
    int face = 0;
    for ( int f = 0; f < 6; f++ ) {
        if ( !get_int_in_vector(f, untouched) ) {
            if ( direction(f, move.axis) == 'r' ) {
                // Moving stickers are in a row.
                faces[f][move.coord] = changed_stickers[face];
            } else if ( direction(f, move.axis) == 'c' ) {
                // Moving stickers are in a column.
                for ( int i = 0; i < 3; i++ ) {
                    faces[f][i][move.coord] = changed_stickers[face][i];
                }
            }
            face++;
        }
    }

    // Rotate the face that was turned.
    int rotated_face_index = move_faces[move.first_char];
    faces[rotated_face_index] = rotate_face(faces[rotated_face_index], move.direction);
}


// Public functions
// ----------------


void Cube::print() {
    // Outputs readable rendering of cube sticker faces to console.

    std::string face_colors[6] = {"green", "orange", "white",
                                  "blue", "red", "yellow"};
    for ( int f = 0; f < 6; f++ ) {
        std::cout << face_colors[f] << std::endl;
        print_2d_vector(faces[f], true);
    }
}


void Cube::execute(std::string moves) {
    // Performs inputted moves on cube.
    // Moves should be in WCA notation and separated by spaces.

    std::istringstream iss(moves);
    vector<std::string> move_strings{std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>{}};
    for ( std::string move : move_strings ) {
        turn(Move(move));
    }
}