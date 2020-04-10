/*=======================================
 op_op.hpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Header file for Old Pochman edges and
 corners algorithm implementation.
========================================*/


#include "../moves.hpp"
#include "../cube.hpp"


char get_adjacent_sticker(char sticker);
MoveString solve_op_op(Cube cube);