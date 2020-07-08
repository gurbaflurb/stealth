#include <iostream>
#include <cstdlib>
#include "b64/b64.h"
#include "net/network.h"
#include "argparser/argparser.h"

int main(int argc, char **argv) {

    try
    {
        argparser arguments(argc, argv, "client");
        
        if(arguments.get_base64_obfuscation()) {
            if(arguments.get_verbose()) {
                std::cout << "Encoding in Base64" << std::endl;
            }
            arguments.set_data(b64::b64_encode(arguments.get_data()));
        }
        if(arguments.get_remote_host() == "") {
            std::cout << arguments.get_data() << std::endl;
        }
        else {
            if(arguments.get_verbose()) {
                std::cout << "Connecting to " << arguments.get_remote_host() << " on port " << arguments.get_port() << std::endl;
            }
            net_conn::makeConnection(arguments.get_remote_host(), arguments.get_data(), arguments.get_port(), arguments);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}