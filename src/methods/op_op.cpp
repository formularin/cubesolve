/*=======================================
 op_op.cpp:                     lol-cubes
 last modified:           Mon, 06/22/2020
 
 Implements the Old Pochman algorithm
 for both edges and corners.
========================================*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <string>

#include "../../include/methods/op_op.hpp"
#include "../../include/cube.hpp"
#include "../../include/moves.hpp"
#include "../../include/utils.hpp"

using std::vector;


char get_edge_sticker_from_coords(int f, int r, int c, Cube cube) {
    // Returns the letter of the edge corresponding to the coords (face, row, column) of `cube`.

    vector<int> sticker_coords = {f, r, c};
    vector<int> adjacent_sticker_coords = adjacent_edge_stickers[sticker_coords];
    int af = adjacent_sticker_coords[0];
    int ar = adjacent_sticker_coords[1];
    int ac = adjacent_sticker_coords[2];

    int sticker_color = cube.faces[f][r][c];
    int adjacent_sticker_color = cube.faces[af][ar][ac];

    vector<int> edge_colors;
    if ( sticker_color < adjacent_sticker_color ) {
        edge_colors.push_back(sticker_color);
        edge_colors.push_back(adjacent_sticker_color);

        return edge_stickers_by_color[edge_colors][0];

    } else {
        edge_colors.push_back(adjacent_sticker_color);
        edge_colors.push_back(sticker_color);

        return edge_stickers_by_color[edge_colors][1];
    }
}


char get_corner_sticker_from_coords(int f, int r, int c, Cube cube) {
    // Returns the letter of the corner corresponding to the coords (face, row, column) of `cube`.

    vector<int> sticker_coords = {f, r, c};
    vector< vector<int> > adjacent_stickers_coords = adjacent_corner_stickers[sticker_coords];

    vector<int> sticker_colors;
    sticker_colors.push_back(cube.faces[f][r][c]);
    for ( vector<int> sticker_coords : adjacent_stickers_coords ) {
        int af = sticker_coords[0];
        int ar = sticker_coords[1];
        int ac = sticker_coords[2];
        sticker_colors.push_back(cube.faces[af][ar][ac]);
    }

    std::sort(sticker_colors.begin(), sticker_colors.end());
    vector<char> sticker_chars = corner_stickers_by_color[sticker_colors];
    
    // Get index of original sticker in sorted list.
    vector<int>::iterator it = std::find(sticker_colors.begin(), sticker_colors.end(), cube.faces[f][r][c]);
    int index = std::distance(sticker_colors.begin(), it);

    return sticker_chars[index];
}


vector<int> get_coords_from_sticker(char sticker) {
    // Gets the coords of a sticker in (face, row, column) format.

    vector<int> coords;
    for ( int f = 0; f < 6; f++ ) {
        for ( int r = 0; r < 3; r++ ) {
            for ( int c = 0; c < 3; c++ ) {
                if ( lettering_scheme[f][r][c] == sticker ) {
                    coords.push_back(f);
                    coords.push_back(r);
                    coords.push_back(c);
                    return coords;
                }
            }
        }
    }
}


std::string solve_op_op(Cube cube) {
    // Returns string containing solution.
    // Cube enters solved state.

    // Whether or not to do an R-permutation after solving edges.
    bool parity;

    // Memorization

    // Edges
    // =========================================

    vector<char> unsolved_edge_stickers = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'};
    vector<char> edge_memo;
   
    // Check for edge pieces that are already solved.

    vector< vector<int> > checked_edge_sticker_coords;

    // Iterate over all coordinate trios of stickers
    for ( int face = 0; face < 6; face++ ) {
        for ( int row = 0; row < 3; row++ ) {
            for ( int col = 0; col < 3; col++ ) {

                // Check if sticker is an edge sticker.
                if ( (row == 0 && col != 1) || (row == 1 && col == 1) || (row == 2 && col != 1) ) continue;

                // Check if sticker is not already checked.
                vector<int> current_sticker_coords = {face, row, col};
                if ( utils::get_vector_in_vector(current_sticker_coords, checked_edge_sticker_coords) ) continue;
                
                // Mark both stickers of edge as checked.
                vector<int> adjacent_sticker_coords = adjacent_edge_stickers[current_sticker_coords];
                checked_edge_sticker_coords.push_back(current_sticker_coords);
                checked_edge_sticker_coords.push_back(adjacent_sticker_coords);

                // Check if sticker has same color as center of face.
                if ( cube.faces[face][1][1] != cube.faces[face][row][col] ) continue;
                
                // Check if adjacent sticker has same color as center of face.
                if (    cube.faces[adjacent_sticker_coords[0]][1][1]
                     != cube.faces[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]) continue;
                
                // If it passed all those tests, both stickers can be removed from the unsolved list.
                unsolved_edge_stickers = utils::remove(unsolved_edge_stickers, lettering_scheme[face][row][col]);
                unsolved_edge_stickers = utils::remove(
                        unsolved_edge_stickers,
                        lettering_scheme[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]
                );
            }
        }
    }
    // Mark 'B' and 'M' (buffer stickers) from unsolved list because they will
    // not manually solved, but will instead be solved by the fact that it is
    // impossible for a rubik's cube to have an odd number of oriented edges.
    unsolved_edge_stickers = utils::remove(unsolved_edge_stickers, 'B');
    unsolved_edge_stickers = utils::remove(unsolved_edge_stickers, 'M');

    // Get edge memo list. Buffer is the red-white edge.
    while ( unsolved_edge_stickers.size() > 0 ) {
        // Whether or not the sticker that was just added to the memo was actually solved.
        bool solved = true;
        if ( edge_memo.size() == 0 ) {
            // First piece.

            char buffer_sticker = get_edge_sticker_from_coords(2, 1, 2, cube);
            if ( buffer_sticker == 'B' || buffer_sticker == 'M' ) {
                // Buffer is already permutated. Replace it with a random unsolved piece.
                for ( int i = 0; buffer_sticker == 'B' || buffer_sticker == 'M'; i++ ) {
                    buffer_sticker = unsolved_edge_stickers[i];
                }
                solved = false;
            }
            edge_memo.push_back(buffer_sticker);
        } else {
            char last_sticker = edge_memo[edge_memo.size() - 1];
            char last_sticker_adjacent = edge_sticker_pairs[last_sticker];
            char next_sticker = unsolved_edge_stickers[0];  // Starts by assuming it is the first sticker in a new cycle.

            int last_edge_occurrences = 0;
            for ( int i = 0; i < edge_memo.size(); i++ ) {
                if ( edge_memo[i] == last_sticker || edge_memo[i] == last_sticker_adjacent ) {
                    last_edge_occurrences++;
                }
            }

            if ( last_edge_occurrences == 2 ) {
                solved = false;
            } else {
                // Find the next sticker in the cycle.

                vector<int> next_sticker_coords = get_coords_from_sticker(last_sticker);
                int f = next_sticker_coords[0];
                int r = next_sticker_coords[1];
                int c = next_sticker_coords[2];
                next_sticker = get_edge_sticker_from_coords(f, r, c, cube);
                for ( int i = 0; next_sticker == 'B' || next_sticker == 'M'; i++ ) {
                    next_sticker = unsolved_edge_stickers[i];
                    solved = false;
                }
            }

            edge_memo.push_back(next_sticker);
        }
        if ( solved ) {
            char next_sticker = edge_memo[edge_memo.size() - 1];

            // Remove both stickers of the edge.
            unsolved_edge_stickers = utils::remove(unsolved_edge_stickers, next_sticker);
            char adjacent_sticker = edge_sticker_pairs[next_sticker];
            unsolved_edge_stickers = utils::remove(unsolved_edge_stickers, adjacent_sticker);
        }
    }

    // Mark parity as true or false based off of whether an odd or even number
    // of edges will be permutated.
    if ( edge_memo.size() % 2 == 1 ) {
        parity = true;
    } else {
        parity = false;
    }

    // Corners
    // =========================================

    vector<char> unsolved_corner_stickers = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'};
    vector<char> corner_memo;

    // Check for corner pieces that are already solved.

    vector< vector<int> > checked_corner_sticker_coords;

    // Iterate over all coordinate trios of stickers.
    for ( int face = 0; face < 6; face++ ) {
        for ( int row = 0; row < 3; row++ ) {
            for ( int col = 0; col < 3; col++ ) {
                
                // Check if sticker is a corner sticker.
                if ( col == 2 || row == 1 ) continue;

                // Check if sticker is not already checked.
                vector<int> current_sticker_coords = {face, row, col};
                if ( utils::get_vector_in_vector(current_sticker_coords, checked_corner_sticker_coords) ) continue;

                // Mark all three stickers of corner as checked.
                vector< vector<int> > adjacent_stickers_coords = adjacent_corner_stickers[current_sticker_coords];
                checked_corner_sticker_coords.push_back(current_sticker_coords);
                for ( vector<int> sticker_coords : adjacent_stickers_coords ) {
                    checked_corner_sticker_coords.push_back(sticker_coords);
                }

                // Check if sticker has same color as center of face.
                if ( cube.faces[face][1][1] != cube.faces[face][row][col] ) continue;

                // Check if adjacent stickers have same color as their faces.
                bool both_solved = true;
                for ( vector<int> sticker_coords : adjacent_stickers_coords ) {
                    if ( cube.faces[sticker_coords[0]][sticker_coords[1]][sticker_coords[2]] != cube.faces[sticker_coords[0]][1][1] ) {
                        both_solved = false;
                    }
                }
                if ( !both_solved ) {
                    continue;
                }

                // If it passed all those tests, all three stickers can be removed from the unsolved list.
                unsolved_corner_stickers = utils::remove(
                    unsolved_corner_stickers, lettering_scheme[face][row][col]);
                for ( vector<int> sticker_coords : adjacent_stickers_coords ) {
                    unsolved_corner_stickers = utils::remove(
                        unsolved_corner_stickers,
                        lettering_scheme[sticker_coords[0]][sticker_coords[1]][sticker_coords[2]]
                    );
                }
            }
        }
    }
    // Mark buffer stickers as solved.
    vector<char> corner_buffer_stickers = {'a', 'e', 'r'};
    for ( char sticker : corner_buffer_stickers ) {
        unsolved_corner_stickers = utils::remove(unsolved_corner_stickers, sticker);
    }

    // Get corner memo list.
    while ( unsolved_corner_stickers.size() > 0 ) {
        // Whether or not the sticker that was just added to the memo was actually solved.
        bool solved = true;
        if ( corner_memo.size() == 0 ) {
            // First piece.

            char buffer_sticker = get_corner_sticker_from_coords(1, 0, 0, cube);
            if ( utils::get_char_in_vector(buffer_sticker, corner_buffer_stickers) ) {
                // Buffer is already permutated. Replace it with a random unsolved piece.
                for ( int i = 0; utils::get_char_in_vector(buffer_sticker, corner_buffer_stickers); i++ ) {
                    buffer_sticker = unsolved_corner_stickers[i];
                }
                solved = false;
            }
            corner_memo.push_back(buffer_sticker);
        } else {
            char last_sticker = corner_memo[corner_memo.size() - 1];
            char next_sticker = unsolved_corner_stickers[0];  // Starts by assuming it is the first sticker in a new cycle.

            vector<char> last_corner_stickers;
            for ( vector<char> trio : corner_sticker_trios ) {
                if ( utils::get_char_in_vector(last_sticker, trio) ) {
                    last_corner_stickers = trio;
                }
            }

            int last_corner_occurrences = 0;
            for ( int i = 0; i < corner_memo.size(); i++ ) {
                if ( utils::get_char_in_vector(corner_memo[i], last_corner_stickers) ) {
                    last_corner_occurrences++;
                }
            }

            if ( last_corner_occurrences == 2 ) {
                solved = false;
            } else {
                // Find the next sticker in the cycle.

                vector<int> next_sticker_coords = get_coords_from_sticker(last_sticker);
                int f = next_sticker_coords[0];
                int r = next_sticker_coords[1];
                int c = next_sticker_coords[2];
                next_sticker = get_corner_sticker_from_coords(f, r, c, cube);
                for ( int i = 0; utils::get_char_in_vector(next_sticker, corner_buffer_stickers); i++ ) {
                    next_sticker = unsolved_corner_stickers[i];
                    solved = false;
                }
            }

            corner_memo.push_back(next_sticker);
        }
        if ( solved ) {
            char next_sticker = corner_memo[corner_memo.size() - 1];

            // Get all three stickers of the corner.
            vector<char> next_corner_stickers;
            for ( vector<char> trio : corner_sticker_trios ) {
                if ( utils::get_char_in_vector(next_sticker, trio) ) {
                    next_corner_stickers = trio;
                }
            }

            // Remove all three stickers of the corner.
            for ( char sticker : next_corner_stickers ) {
                unsolved_corner_stickers = utils::remove(unsolved_corner_stickers, sticker);
            }
        }
    }

    // Execution

    std::string solution;

    // Edges
    // =========================================

    for ( char edge : edge_memo ) {
        std::string edge_algorithm = edge_algorithms[edge];
        if ( edge != 'D' ) {
            edge_algorithm += " ";
        }

        solution += (edge_algorithm);
        solution += (edge_swap_algorithm + " ");
        solution += (get_inverse_moves(edge_algorithms[edge]));
    }

    // Parity
    // =========================================

    if ( parity ) {
        solution += parity_algorithm + " ";
    }

    // Corners
    // =========================================

    return solution;
}