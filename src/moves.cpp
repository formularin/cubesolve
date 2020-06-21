/*=======================================
 moves.cpp:                     lol-cubes
 last modified:           Sun, 06/21/2020
 
 Implemenations of methods for the
 Move class.
========================================*/


#include <iostream>
#include <string>
#include <sstream>

#include <boost/algorithm/string/join.hpp>

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


std::string get_inverse_moves(std::string moves) {
    // Gets the inverse of the moves notated by string `moves`.
    // Inverse meaning that if `moves` are executed on a solved cube,
    // `get_inverse_moves(moves)` will return it to the solved state.

    vector<std::string> inverse_moves;
    
    std::istringstream iss(moves);
    vector<std::string> move_strings{std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>{}};

    for ( int m = move_strings.size() - 1; m >= 0; m-- ) {

        std::string inverse_move;

        inverse_move.push_back(move_strings[m].at(0));

        if ( move_strings[m].size() == 2 ) {
            if ( move_strings[m].at(1) == '2' ) {
                inverse_move.push_back('2');
            }
        } else {
            inverse_move.push_back('\'');
        }

        inverse_moves.push_back(inverse_move);
    }

    std::string inverse_moves_string = boost::algorithm::join(inverse_moves, " ");
    return inverse_moves_string;
}