#ifndef __B64__
#define __B64__

#include <iostream>
#include <cstdlib>
#include <bitset>

namespace b64 {
    
    std::string b64_encode(std::string);
    std::string b64_decode(std::string);

    std::string b64_file_encode(std::string);
    std::string b64_input_encode(std::string);

    char b64_shift_down(char, int);
    char b64_shift_up(char, int);

    char b64_get_decoded_binary(char);

}
#endif