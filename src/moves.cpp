/*=======================================
 moves.cpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Implemenations of methods for Move and
 MoveString classes.
========================================*/


#include <iostream>
#include <string>

#include "../include/moves.hpp"
#include "../include/utils.hpp"


// ***********************
// Move
// ***********************


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


// ***********************
// MoveString
// ***********************


MoveString::MoveString(vector<Move> move_string) {
    // MoveString class constructor.

    moves = move_string;
}


void MoveString::print() {
    // Prints a string that can be interpreted by a human.

    vector<int> comment_indices;
    for ( std::map<int, std::string>::iterator it = comments.begin();
          it != comments.end(); ++it ) {
        comment_indices.push_back(it -> first);
    }

    for ( int i = 0; i < moves.size(); i++ ) {
        if ( get_int_in_vector(i, comment_indices) ) {
            std::cout << "  //" << comments[i] << std::endl;
        }
        std::cout << moves[i].move << " ";
    }
}