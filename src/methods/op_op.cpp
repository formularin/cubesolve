/*=======================================
 op_op.cpp:                     lol-cubes
 last modified:           Sat, 06/20/2020
 
 Implements the Old Pochman algorithm
 for both edges and corners.
========================================*/


#include <algorithm>
#include <iostream>
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


MoveString solve_op_op(Cube cube) {
    // Returns MoveString containing solution and explanatory comments.
    // Cube enters solved state.

    vector<Move> solution_moves;

    // Memorization

    // Edges
    // =========================================

    vector<char> unsolved_edge_stickers = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'};
    vector<char> edge_memo;
   
    // Check for edge pieces that are already solved.

    vector< vector<int> > checked_sticker_coords;

    // Iterate over all coordinate pairs of stickers
    for ( int face = 0; face < 6; face++ ) {
        for ( int row = 0; row < 3; row++ ) {
            for ( int col = 0; col < 3; col++ ) {

                // Check if sticker is an edge sticker.
                if ( (row == 0 && col != 1) || (row == 1 && col == 1) || (row == 2 && col != 1) ) continue;

                // Check if sticker is not already checked.
                vector<int> current_sticker_coords = {face, row, col};
                if ( get_vector_in_vector(current_sticker_coords, checked_sticker_coords) ) continue;
                
                // Mark both stickers of edge as checked.
                vector<int> adjacent_sticker_coords = adjacent_edge_stickers[current_sticker_coords];
                checked_sticker_coords.push_back(current_sticker_coords);
                checked_sticker_coords.push_back(adjacent_sticker_coords);

                // Check if sticker has same color as center of face.
                if ( cube.faces[face][1][1] != cube.faces[face][row][col] ) continue;
                
                // Check if adjacent sticker has same color as center of face.
                if (    cube.faces[adjacent_sticker_coords[0]][1][1]
                     != cube.faces[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]) continue;
                
                // If it passed all those tests, both stickers can be removed from the unsolved list.
                unsolved_edge_stickers.erase(
                    remove(unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(), lettering_scheme[face][row][col]),
                    unsolved_edge_stickers.end()
                );
                unsolved_edge_stickers.erase(
                    remove(
                        unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(),
                        lettering_scheme[adjacent_sticker_coords[0]][adjacent_sticker_coords[1]][adjacent_sticker_coords[2]]
                    ),
                    unsolved_edge_stickers.end()
                );
            }
        }
    }
    // Mark 'B' and 'M' (buffer stickers) from unsolved list because they will
    // not manually solved, but will instead be solved by the fact that it is
    // impossible for a rubik's cube to have an odd number of oriented edges.
    unsolved_edge_stickers.erase(
        remove(unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(), 'B'),
        unsolved_edge_stickers.end()
    );
    unsolved_edge_stickers.erase(
        remove(unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(), 'M'),
        unsolved_edge_stickers.end()
    );

    // Get memo list. Buffer is the red-white edge.
    while ( unsolved_edge_stickers.size() > 0 ) {
        // Whether or not the sticker that was just added to the memo was actually solved.
        char solved = true;
        if ( edge_memo.size() == 0 ) {
            // First piece.

            char buffer_sticker = get_edge_sticker_from_coords(2, 1, 2, cube);
            if ( buffer_sticker == 'B' || buffer_sticker == 'M' ) {
                // Buffer is already permutated. Replace is with a random unsolved piece.
                for ( int i = 1; buffer_sticker == 'B' || buffer_sticker == 'M'; i++ ) {
                    buffer_sticker = unsolved_edge_stickers[i];
                }
                solved = false;
            } else {
                edge_memo.push_back(buffer_sticker);
            }

        } else {
            char last_sticker = edge_memo[edge_memo.size() - 1];
            char last_sticker_adjacent = edge_sticker_pairs[last_sticker];
            char next_sticker = unsolved_edge_stickers[0];  // Starts by assuming it is the first sticker in a new cycle.

            int last_sticker_occurrences = 0;
            for ( int i = 0; i < edge_memo.size(); i++ ) {
                if ( edge_memo[i] == last_sticker || edge_memo[i] == last_sticker_adjacent ) {
                    last_sticker_occurrences++;
                }
            }

            if ( last_sticker_occurrences == 2 ) {
                solved = false;
            } else {
                // Finding the next sticker in the cycle.

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
            unsolved_edge_stickers.erase(
                remove(unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(), next_sticker),
                unsolved_edge_stickers.end()
            );
            char adjacent_sticker = edge_sticker_pairs[next_sticker];
            unsolved_edge_stickers.erase(
                remove(unsolved_edge_stickers.begin(), unsolved_edge_stickers.end(), adjacent_sticker),
                unsolved_edge_stickers.end()
            );
        }
    }

    std::cout << "edge memo: ";
    for ( char sticker : edge_memo ) {
        std::cout << sticker << " ";
    }
    std::cout << std::endl;

    return MoveString({Move("R")});
}