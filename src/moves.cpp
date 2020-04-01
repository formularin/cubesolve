/*=======================================
 moves.cpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Implemenations of methods for Move and
 MoveString classes.
========================================*/


#include <iostream>
#include <string>

#include "../include/moves.hpp"


Move::Move(std::string move_string) {
    // Move class constructor.

    move = move_string;

    char last_char = move_string.at(move_string.size() - 1);
    char first_char = move_string.at(0);

    if ( last_char == '2' ) {
        rotations = 2;
    } else {
        rotations = 1;
    }

    int axis = move_axes[first_char];
    int coords = move_coords[first_char];

    if ( last_char != '\'' ) {
        // Move is prime
        direction = move_directions[first_char];
    } else {
        if ( move_directions[first_char] == "C" ) {
            direction = "CC";
        } else {
            direction = "C";
        }
    }

}