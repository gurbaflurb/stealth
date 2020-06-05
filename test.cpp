#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "b64/b64.h"

int main(int argc, char **argv) {

    char currentLetter = 'T';

    std::cout << (char)((b64::b64_get_decoded_binary(currentLetter)<<2)+0b00000001) << std::endl;
    
    return 0;
}