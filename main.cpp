#include <iostream>
#include <cstdlib>
#include "b64/b64.h"
#include "net/network.h"
#include "argparser/argparser.h"

int main(int argc, char **argv) {
    
    try
    {
        argparser arguments(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}