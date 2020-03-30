/*=======================================
 utils.hpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 Useful function implementations.
========================================*/


#include <algorithm>
#include <vector>

#include "../include/utils.hpp"

using std::vector;


bool get_int_in_vector(int i, vector<int> vec) {
    return std::find(vec.begin(), vec.end(), i) != vec.end;
}