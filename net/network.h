#ifndef __NETWORK__
#define __NETWORK__

#define BUFLEN 2048
#include <iostream>
#include <cstdlib>

namespace net_conn {

    extern std::string fake_http_header;
    
    void makeConnection(std::string addr, int port, std::string msg);

}
#endif