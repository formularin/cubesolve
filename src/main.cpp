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
        if ( std::strcmp(argv[1 + x], "auto") == 0 ) {
            cube.scramble();
        } else {
            cube.execute(argv[1 + x]);
        }

        // Draw scramble if necessary.
        if ( x == 1 ) {
            cube.print();
        }

        // Solve cube and print solution.
        if ( std::strcmp(argv[2 + x], "opop") == 0 ) {
            std::string solution = solve_op_op(cube);
            std::cout << solution << std::endl;
        } else if ( std::strcmp(argv[2 + x], "lbl") == 0 | std::strcmp(argv[2 + x], "is") == 0 ) {
            std::cout << "Method not yet implemented." << std::endl;
        }

    } catch (int x) {
        std::cout << "Usage: cubesolve [-d] <scramble> <method>" << std::endl;
    }

    return 0;
}