#include <iostream>
#include <cstdlib>
#include "network.h"

namespace net_conn {

     std::string fake_http_header = "GET / HTTP/1.1\n"
                                    "Host: www.website.com\n"
                                    "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:77.0) Gecko/20100101 Firefox/77.0\n"
                                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n"
                                    "Accept-Language: en-us,en;q=0.5\n"
                                    "Accept-Encoding: gzip,deflate\n"
                                    "Keep-Alive: 300\n"
                                    "Connection: keep-alive\n"
                                    "Pragma: no-cache\n"
                                    "Cache-Control: no-cache\n\n";;

     #ifdef __linux__
     #include <stdio.h>
     #include <sys/socket.h>
     #include <arpa/inet.h>
     #include <unistd.h>
     #include <string.h>

     void makeConnection(std::string addr, int port, std::string msg) {
          int sock = 0, valread;
          struct sockaddr_in serv_addr;
          const char *socketMsg = msg.c_str();
          char buffer[BUFLEN] = {0};
          
          serv_addr.sin_family = AF_INET;
          serv_addr.sin_port = htons(port);

          if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
               throw std::runtime_error("Error creating socket");
          }

          if(inet_pton(AF_INET, addr.c_str(), &serv_addr.sin_addr) <= 0) {
               throw std::runtime_error("Invalid address or Address is not currently supported");
          }

          if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
               throw std::runtime_error("Failed to connect to remote server");
          }

          valread = read(sock, buffer, BUFLEN);
          std::cout << "Server sent: " << buffer << std::endl;
          send(sock, socketMsg, strlen(socketMsg), 0);
          valread = read(sock, buffer, BUFLEN);
          std::cout << "Server sent: " << buffer << std::endl;
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

     #endif

}
