/*=======================================
 utils.hpp:                     lol-cubes
 last modified:           Sat, 06/20/2020
 
 Useful functions.
========================================*/


#include <string>
#include <vector>

using std::vector;


bool get_char_in_vector(char c, vector<char> vec);
bool get_int_in_vector(int i, vector<int> vec);
bool get_string_in_vector(std::string string, vector<std::string> vec);
bool get_vector_in_vector(vector<int> v, vector< vector<int> > vec);
void print_sticker_row(vector<int> stickers);
void print_int_vector(vector<int> vec);
vector< vector<int> > rotate_face(vector< vector<int> > face, std::string direction);