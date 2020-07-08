#ifndef __NETWORK__
#define __NETWORK__

#define BUFLEN 2048
#include <iostream>
#include <cstdlib>
#include "../argparser/argparser.h"

namespace net_conn {

    extern std::string fake_http_header;
    
    void makeConnection(std::string, std::string, int, argparser);

    void server(int, argparser);

}
#endif