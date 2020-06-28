#include <iostream>
#include <cstdlib>
#include "net/network.h"

int main() {

    std::string message = "";

    try
    {
        net_conn::makeConnection("", message, 1337);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}