/*=======================================
 moves.cpp:                     lol-cubes
 last modified:           Sun, 06/21/2020
 
 Implemenations of methods for the
 Move class.
========================================*/


#include <iostream>
#include <iterator>
#include <map>
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


std::string cancel_moves(vector<std::string> moves) {
    // Takes a string of moves all on the same face, and adds them up to see
    // the single move that would be equivalent to doing all of those moves.

    std::string final_move(1, moves[0].at(0));

    int quarter_turns = 0;
    for ( std::string move : moves ) {
        if ( move.size() > 1 ) {
            if ( move.at(1) == '2' ) {
                quarter_turns += 2;
            } else {
                quarter_turns--;
            }
        } else {
            quarter_turns++;
        }
    }

    int modded_quarter_turns = utils::mod(quarter_turns, 4);

    if ( modded_quarter_turns == 0 ) {
        final_move = "";
    } else if ( modded_quarter_turns == 2 ) {
        final_move.push_back('2');
    } else if ( modded_quarter_turns == 3 ) {
        final_move.push_back('\'');
    }

    return final_move;
}


std::string cancel_redundant_moves(std::string moves) {
    // Takes a string and combines moves to remove all redundancies.

    vector<std::string> final_moves;

    std::istringstream iss(moves);
    vector<std::string> move_strings{std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>{}};
    
    std::map< char, vector<std::string> > current_moves_by_face = {
        { 'R', {} },
        { 'L', {} },
        { 'F', {} },
        { 'B', {} },
        { 'U', {} },
        { 'D', {} }
    };

    for ( int i = 0; i < move_strings.size(); i++ ) {

        std::string move = move_strings[i];

        std::map< char, vector<std::string> >::iterator it = current_moves_by_face.begin();

        while ( it != current_moves_by_face.end() ) {

            if ( it->first != move.at(0) && it->first != axis_pairs[move.at(0)] ) {
                // These are the current moves of a different axis.
                // Clear them because a move on this axis just broke the chain.

                if ( it->second.size() > 0 ) {
                    std::string canceled_moves = cancel_moves(it->second);
                    it->second.clear();
                    if ( canceled_moves.compare("") != 0 ) {
                        // The canceled moves add up to something.
                        final_moves.push_back(canceled_moves);
                    }
                }
            } else if ( it->first == move.at(0) ) {
                it->second.push_back(move);
            }

            it++;
        }
    }

    std::string final_moves_string = boost::algorithm::join(final_moves, " ");
    return final_moves_string;
}