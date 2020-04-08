/*=======================================
 main.cpp:                      lol-cubes
 last modified:               Wed, Apr 08
 
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
        std::string scramble = argv[1];
        cube.execute(scramble);
        cube.print();
        if ( argv[2] == "opop" ) {
            MoveString solution = solve_op_op(cube);
            solution.print();
        }
    } catch (int x) {
        std::cout << "Usage: cubesolve <scramble> <method>" << std::endl;
    }

    return 0;
}