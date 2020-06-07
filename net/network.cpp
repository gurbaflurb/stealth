#include <iostream>
#include <cstdlib>
#include "network.h"

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

     #pragma comment (lib, "ws2_32.lib")

     void makeConnection(std::string addr, int port, std::string msg) {
          WSAData wsaData;
          SOCKET client;
          const char *socketAddr = addr.c_str();
          struct sockaddr_in server;
          const char *message = msg.c_str();
          char server_reply[BUFLEN];
          int recv_size;

          if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) { // Initializes winsock library
               throw std::runtime_error("Error creating Winsock error: " + WSAGetLastError()); // Gets Winsock error code
          }

          if((client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) { // creates a TCP socket
               throw std::runtime_error("Failed to create socket: " + WSAGetLastError());
          }

          server.sin_addr.s_addr = inet_addr(socketAddr); // converts address into useable address
          server.sin_family = AF_INET;
          server.sin_port = htons(port);

          if(connect(client, (struct sockaddr *)&server, sizeof(server)) < 0) {
               throw std::runtime_error("Failed to connect to server!");
          }
          std::cout << "Connected to server " << addr << "!" << std::endl;
          
          if((recv_size = recv(client, server_reply, BUFLEN, 0)) == SOCKET_ERROR) {
               throw std::runtime_error("Recv failed!");
          }
          server_reply[recv_size] = '\0';
          std::cout << server_reply << std::endl;

          if(send(client, message, strlen(message), 0) < 0) {
               throw std::runtime_error("Failure to send message");
          }

          if((recv_size = recv(client, server_reply, BUFLEN, 0)) == SOCKET_ERROR) {
               throw std::runtime_error("Recv failed!");
          }
          server_reply[recv_size] = '\0';
          std::cout << server_reply << std::endl;

          closesocket(client);
          WSACleanup();
     }

}
#endif