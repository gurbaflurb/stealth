#ifndef __NETWORK__
#define __NETWORK__

#define BUFLEN 2048
#include <iostream>
#include <cstdlib>

namespace net_conn {

    void makeConnection(std::string addr, int port, std::string msg);

}
#endif