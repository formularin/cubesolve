/*=======================================
 main.cpp:                      lol-cubes
 last modified:           Tue, 06/16/2020
 
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
    try {
        if ( std::strcmp(argv[1], "auto") == 0 ) {
            cube.scramble();
        } else {
            cube.execute(argv[1]);
            std::cout << argv[1] << std::endl;
        }
        cube.print();
        if ( std::strcmp(argv[2], "opop") == 0 ) {
            MoveString solution = solve_op_op(cube);
            std::cout << "solution: ";
            solution.print();
        }
    } catch (int x) {
        std::cout << "Usage: cubesolve <scramble> <method>" << std::endl;
    }

    return 0;
}