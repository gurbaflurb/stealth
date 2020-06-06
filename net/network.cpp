#include "network.h"
#include <iostream>
#include <cstdlib>

namespace net_conn {

     #ifdef __linux__
     #include <unistd.h>
     #include <netdb.h>
     #include <sys/types.h>
     #include <sys/socket.h>
     #include <netinet/in.h>

     void makeConnection(std::string addr, int port, std::string msg) {
     int sockfd, portno, n;
     struct sockaddr_in serv_addr;
     struct hostent *server;

     char buffer[BUFLEN];

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     server = gethostbyname(addr);

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);

     serv_addr.sin_port = htons(portno);
     if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
          error("ERROR connecting");
     printf("Please enter the message: ");
     bzero(buffer,BUFLEN);
     fgets(buffer,BUFLEN -1,stdin);
     n = write(sockfd,buffer,strlen(buffer));
     if (n < 0) 
          error("ERROR writing to socket");
     bzero(buffer,BUFLEN);
     n = read(sockfd,buffer,BUFLEN-1);
     if (n < 0) 
          error("ERROR reading from socket");
     printf("%s\n",buffer);
     close(sockfd);
     return 0;
     }

     #elif __WIN32
     #include <windows.h>
     #include <winsock2.h>
     #include <ws2tcpip.h>

     //#pragma comment (lib, "Ws2_32.lib")
     //#pragma comment (lib, "Mswsock.lib")
     //#pragma comment (lib, "AdvApi32.lib")

     void makeConnection(std::string addr, int port, std::string msg) {
     
     }

}
#endif