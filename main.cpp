#include <iostream>
#include <cstdlib>
#include "b64/b64.h"
#include "net/network.h"
#include "argparser/argparser.h"

int main(int argc, char **argv) {
    
    try
    {
        argparser arguments(argc, argv);
        net_conn::makeConnection(arguments.get_remote_host(), arguments.get_port(), "General Kenobi!");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    
    
    return 0;
}