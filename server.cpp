#include <iostream>
#include <cstdlib>
#include "b64/b64.h"
#include "net/network.h"
#include "argparser/argparser.h"

int main(int argc, char **argv) {
    
    try {
        argparser arguments(argc, argv, "server");
        
        if(arguments.get_base64_obfuscation() && arguments.get_verbose()) {
            std::cout << "Decoding with Base64" << std::endl;
        }
        net_conn::server(arguments.get_port(), arguments);
    }
    catch(const std::exception& e) {
        std::cerr << "An error has occured:\n" << e.what() << '\n';
    }
    
    return 0;
}