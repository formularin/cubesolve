/*=======================================
 utils.hpp:                     lol-cubes
 last modified:               Mon, Mar 30
 
 Useful functions.
========================================*/


#include <string>
#include <vector>

using std::vector;


bool get_int_in_vector(int i, vector<int> vec);
void print_sticker_row(vector<int> stickers);
vector< vector<int> > rotate_face(vector< vector<int> > face, std::string direction);