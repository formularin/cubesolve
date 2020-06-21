/*=======================================
 moves.cpp:                     lol-cubes
 last modified:           Sun, 06/21/2020
 
 Implemenations of methods for the
 Move class.
========================================*/


#include <iostream>
#include <string>

#include "../include/moves.hpp"
#include "../include/utils.hpp"


Move::Move(std::string move_string) {
    // Move class constructor.

    move = move_string;

    char last_char = move_string.at(move_string.size() - 1);
    first_char = move_string.at(0);

    axis = move_axes[first_char];
    coords = move_coords[first_char];

    if ( last_char != '\'' ) {
        // Move is not prime.
        direction = "C";
    } else {
        // Move is prime.
        direction = "CC";
    }

}