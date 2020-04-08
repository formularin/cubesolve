/*=======================================
 main.cpp:                     lol-cubes
 last modified:               Tue, Mar 31
 
 Rubik's cube solver written in c++.
========================================*/


#include <iostream>
#include <string>
#include <vector>

#include "../include/cube.hpp"

using std::vector;


int main(int argc, char** argv) {

    Cube cube = Cube();
    try {
        std::string scramble = argv[1];
        cube.execute(scramble);
        cube.print();
    } catch (int x) {
        std::cout << "Usage: cubesolve <scramble> <method>" << std::endl;
    }

    return 0;
}