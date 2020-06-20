/*=======================================
 utils.hpp:                     lol-cubes
 last modified:           Sat, 06/20/2020
 
 Useful functions.
========================================*/


#include <string>
#include <vector>


namespace utils {
    bool get_char_in_vector(char c, std::vector<char> vec);
    bool get_int_in_vector(int i, std::vector<int> vec);
    bool get_string_in_vector(std::string string, std::vector<std::string> vec);
    bool get_vector_in_vector(std::vector<int> v, std::vector< std::vector<int> > vec);
    void print_sticker_row(std::vector<int> stickers);
    void print_int_vector(std::vector<int> vec);
    std::vector< std::vector<int> > rotate_face(std::vector< std::vector<int> > face, std::string direction);
    std::vector<char> remove(std::vector<char> vec, char c);
}