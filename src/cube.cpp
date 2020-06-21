/*=======================================
 cube.cpp:                      lol-cubes
 last modified:           Sun, 06/21/2020
 
 Implementations for the `Cube` class.
========================================*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <random>

#include <boost/algorithm/string/join.hpp>

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


std::string Cube::choose_move(vector<std::string> current_moves,
                              vector< vector<std::string> > axes,
                              vector< vector<std::string> > sides) {
    // Chooses a move based of a list of moves already chosen that isn't redundant.
    // Translated from:
    // https://github.com/lol-cubes/cl-timer/blob/master/cl_timer/scramble.py

    std::string move = move_notations[std::rand() % move_notations.size()];
    
    // Find which axis and which side the move belongs to.
    vector<std::string> move_axis;
    for ( vector<std::string> axis : axes ) {
        if ( utils::get_string_in_vector(move, axis) ) {
            move_axis = axis;
        }
    }
    vector<std::string> move_side;
    for ( vector<std::string> side : sides ) {
        if ( utils::get_string_in_vector(move, side) ) {
            move_side = side;
        }
    }

    // Previous moves of the same axis.
    int last_move_of_different_axis = -1;
    for ( int m = 0; m < current_moves.size(); m++ ) {
        if ( !utils::get_string_in_vector(current_moves[m], move_axis) ) {
            last_move_of_different_axis = m;
        }
    }

    // Find if any moves of the same side as `move`
    // have been done since the last move of a different axis.
    for ( int m = current_moves.size() - 1; m > last_move_of_different_axis; m-- ) {
        if ( utils::get_string_in_vector(current_moves[m], move_side) ) {
            return choose_move(current_moves, axes, sides);
        }
    }
    return move;
}


// Public functions
// ----------------


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
        if ( !utils::get_int_in_vector(f, untouched) ) {
            // Get list of faces whose row or col of pieces moved should be reversed.
            vector< vector<int> > face = faces[f];
            vector<int> reversed_faces;
            if        ( (move.first_char == 'R' && move.direction == "CC")
                     || (move.first_char == 'L' && move.direction == "C") ) {
                reversed_faces = {3, 5};
            } else if ( (move.first_char == 'R' && move.direction == "C")
                     || (move.first_char == 'L' && move.direction == "CC") ) {
                reversed_faces = {2, 3};
            } else if ( (move.first_char == 'F' && move.direction == "CC")
                     || (move.first_char == 'B' && move.direction == "C") ) {
                reversed_faces = {2, 5};
            } else if ( (move.first_char == 'F' && move.direction == "C")
                     || (move.first_char == 'B' && move.direction == "CC") ) {
                reversed_faces = {4, 1};
            }
            bool face_is_reversed;
            if ( utils::get_int_in_vector(f, reversed_faces) ) {
                face_is_reversed = true;
            } else {
                face_is_reversed = false;
            }

            if ( direction(f, move.axis) == 'r' ) {
                // Moving stickers are in a row.
                if ( face_is_reversed ) {
                    vector<int> face_changing_stickers;
                    face_changing_stickers = face[std::abs(move.coords[f] - 2)];
                    std::reverse(face_changing_stickers.begin(),
                                 face_changing_stickers.end());
                    changing_stickers.push_back(face_changing_stickers);
                } else {
                    changing_stickers.push_back(face[std::abs(move.coords[f] - 2)]);
                }
            } else if ( direction(f, move.axis) == 'c' ) {
                // Moving stickers are in a column.
                vector<int> face_changing_stickers;
                for ( int i = 0; i < 3; i++ ) {
                    if ( face_is_reversed ) {
                        face_changing_stickers.push_back(face[2 - i][move.coords[f]]);
                    } else {
                        face_changing_stickers.push_back(face[i][move.coords[f]]);
                    }
                }
                changing_stickers.push_back(face_changing_stickers);
            }
        }
    }

    // Get list of all changed stickers.
    vector< vector<int> > changed_stickers(4, vector<int>(3));

    // Turns whose directions need to be swapped.
    vector<char> backwards_moves = {'L', 'B', 'D'};
    bool backwards_move = std::find(
            backwards_moves.begin(),
            backwards_moves.end(),
            move.first_char
        ) != backwards_moves.end();
    if (
            (move.direction == "C" && !backwards_move)
         || (move.direction == "CC" && backwards_move) ) {
        changed_stickers[0] = changing_stickers[3];
        for ( int i = 1; i < 4; i++ ) {
            changed_stickers[i] = changing_stickers[i - 1];
        }
    } else if (
            (move.direction == "CC" && !backwards_move)
         || (move.direction == "C" && backwards_move) ) {
        changed_stickers[3] = changing_stickers[0];
        for ( int i = 0; i < 3; i++ ) {
            changed_stickers[i] = changing_stickers[i + 1];
        }
    }

    // Apply changed stickers to faces.
    int face = 0;
    for ( int f = 0; f < 6; f++ ) {
        if ( !utils::get_int_in_vector(f, untouched) ) {
            if ( direction(f, move.axis) == 'r' ) {
                // Moving stickers are in a row.
                faces[f][std::abs(move.coords[f] - 2)] = changed_stickers[face];
            } else if ( direction(f, move.axis) == 'c' ) {
                // Moving stickers are in a column.
                for ( int i = 0; i < 3; i++ ) {
                    faces[f][i][move.coords[f]] = changed_stickers[face][i];
                }
            }
            face++;
        }
    }

    // Rotate the face that was turned.
    int rotated_face_index = move_faces[move.first_char];
    faces[rotated_face_index] = utils::rotate_face(faces[rotated_face_index], move.direction);
}


void Cube::print() {
    // Outputs readable rendering of cube sticker faces to console.

    for ( vector<int> row : faces[2] ) {
        std::cout << "       ";
        utils::print_sticker_row(row);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    vector<int> middle_faces = {1, 0, 4, 3};
    for ( int i = 0; i < 3; i++ ) {
        for ( int f : middle_faces ) {
            utils::print_sticker_row(faces[f][i]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for ( vector<int> row : faces[5] ) {
        std::cout << "       ";
        utils::print_sticker_row(row);
        std::cout << std::endl;
    }
}


void Cube::execute(std::string moves) {
    // Performs inputted moves on cube.
    // Moves should be in WCA notation and separated by spaces.

    std::istringstream iss(moves);
    vector<std::string> move_strings{std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>{}};
    for ( std::string move : move_strings ) {
        if ( move.length() > 1 && move.at(1) == '2' ) {
            std::string first_char;
            first_char.push_back(move.at(0));
            for ( int i = 0; i < 2; i++ ) {
                turn(Move(first_char));
            }
        } else {
            turn(Move(move));
        }
    }
}


std::string Cube::scramble() {
    // Executes a random set of 20 moves on the cube. Also returns scramble string.

    // Get possible moves grouped by axis.
    vector< vector<std::string> > axes(3, vector<std::string>());
    for ( int m = 0; m < move_notations.size(); m++ ) {
        axes[m / 6].push_back(move_notations[m]);
    }

    // Get possible moves grouped by side.
    vector< vector<std::string> > sides(6, vector<std::string>());
    for ( int m = 0; m < move_notations.size(); m++ ) {
        sides[m / 3].push_back(move_notations[m]);
    }

    std::srand(std::time(NULL));  // Seed random numbers.
    vector<std::string> scramble_moves;
    for ( int i = 0; i < 20; i++ ) {
        scramble_moves.push_back(choose_move(scramble_moves, axes, sides));
    }

    std::string scramble_string = boost::algorithm::join(scramble_moves, " ");
    
    execute(scramble_string);
    return scramble_string;
}