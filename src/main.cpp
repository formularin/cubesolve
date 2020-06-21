/*=======================================
 main.cpp:                      lol-cubes
 last modified:           Sun, 06/21/2020
 
 Rubik's cube solver written in c++.
========================================*/


#include <iostream>
#include <string>
#include <vector>

#include "../include/cube.hpp"
#include "../include/moves.hpp"

// Solution functions
#include "../include/methods/op_op.hpp"

using std::vector;


int main(int argc, char** argv) {

    Cube cube = Cube();
    int x = 0;
    try {

        if ( std::strcmp(argv[1], "-d") == 0 ) {
            x++;
        }

        // Scramble cube.
        std::string scramble;
        if ( std::strcmp(argv[1 + x], "auto") == 0 ) {
            scramble = cube.scramble();
        } else {
            cube.execute(argv[1 + x]);
            scramble = argv[1 + x];
        }

        // Draw scramble if necessary.
        if ( x == 1 ) {
            std::cout << ("scramble: " + scramble) << std::endl;
            cube.print();
        }

        // Solve cube and print solution.
        std::string solution;

        if ( std::strcmp(argv[2 + x], "opop") == 0 ) {
            solution = solve_op_op(cube);

        } else if ( std::strcmp(argv[2 + x], "lbl") == 0 ) {
            solution = "Method not yet implemented.";

        } else if ( std::strcmp(argv[2 + x], "is") == 0 ) {
            solution = get_inverse_moves(scramble);   
        }
        std::cout << solution << std::endl;

    } catch (int x) {
        std::cout << "Usage: cubesolve [-d] <scramble> <method>" << std::endl;
    }

    return 0;
}