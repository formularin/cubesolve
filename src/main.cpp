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
    cube.execute("R U");
    cube.print();

    return 0;
}