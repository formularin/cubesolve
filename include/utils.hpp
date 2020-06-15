/*=======================================
 utils.hpp:                     lol-cubes
 last modified:               Wed, Apr 08
 
 Useful functions.
========================================*/


#include <string>
#include <vector>

using std::vector;


bool get_int_in_vector(int i, vector<int> vec);
bool get_string_in_vector(std::string string, vector<std::string> vec);
void print_sticker_row(vector<int> stickers);
vector< vector<int> > rotate_face(vector< vector<int> > face, std::string direction);