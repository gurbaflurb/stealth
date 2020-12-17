#include <iostream>
#include <cstdlib>
#include "network.h"
#include "../b64/b64.h"

namespace net_conn {

     std::string fake_http_header = "GET / HTTP/1.1\n\r"
                                    "Host: www.website.com\n\r"
                                    "User-Agent: Perseverance/1.0 (Windows NT 10.0; Win64; x64; rv:77.0) Gecko/20100101 Perseverance/1.5\n\r"
                                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n\r"
                                    "Accept-Language: en-us,en;q=0.5\n\r"
                                    "Accept-Encoding: gzip,deflate\n\r"
                                    "Keep-Alive: 300\n\r"
                                    "Connection: keep-alive\n\r"
                                    "Pragma: no-cache\n\r"
                                    "Cache-Control: no-cache\n\r\n\r";
     

     #ifdef __linux__
     #include <stdio.h>
     #include <sys/socket.h>
     #include <arpa/inet.h>
     #include <unistd.h>
     #include <string.h>

     void makeConnection(std::string addr, std::string msg, int port, argparser arguments) {
          int sock = 0, valread;
          struct sockaddr_in serv_addr;
          char buffer[BUFLEN] = {0};
          const char *sendBuf;
          
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

          while(true) {
               std::cout << "> ";
               std::getline(std::cin, msg);

               if(arguments.get_base64_obfuscation()) {
                    msg = b64::b64_encode(msg);
               }

               sendBuf = msg.c_str();
               std::cout << "Sending: " << sendBuf << std::endl;

               send(sock, msg.c_str(), strlen(msg.c_str()), 0);

               valread = read(sock, buffer, BUFLEN);
               if(arguments.get_base64_obfuscation()) {
                    std::string temp = b64::b64_decode((std::string)buffer);
                    temp.copy(buffer, temp.size()+1);
                    buffer[temp.size()] = '\0';
               }
               std::cout << "Server sent: " << buffer << std::endl;
               break; // remove this to keep a back and forth with connected server
          }
          
     }

     void server(int port, argparser arguments) {
          int server_fd, new_socket, valread;
          struct sockaddr_in address;
          int opt = 1;
          int addrlen = sizeof(address);
          char buffer[BUFLEN] = {0};
          std::string reply = "200 Ok";

          if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
               throw std::runtime_error("Error creating socket!");
          }

          if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
               throw std::runtime_error("Setsockopt error!");
          }

          address.sin_family = AF_INET;
          address.sin_addr.s_addr = INADDR_ANY;
          address.sin_port = htons(port);

          if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
               throw std::runtime_error("Failed to bind to port!");
          }
          std::cout << "Bound to port: " << port << std::endl; 
          
          if(listen(server_fd, 10) < 0) {
               throw std::runtime_error("Failed to listen!");
          }
          std::cout << "Listening for new connections" << std::endl;
          
          if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
               throw std::runtime_error("Failed to accept connection");
          }
          std::cout << "Connection recieved!" << std::endl;

          while(true) {
               valread = read(new_socket, buffer, BUFLEN);
               if(arguments.get_base64_obfuscation()) {
                    std::cout << b64::b64_decode((std::string)buffer) << std::endl;
                    reply = b64::b64_encode(reply).c_str();
               }
               else {
                    std::cout << buffer << std::endl;
               }
               send(new_socket, reply.c_str(), strlen(reply.c_str()), 0);
               break; // remove this to keep a back and forth with connected client
          }
     }

     #elif __WIN32
     #include <windows.h>
     #include <winsock2.h>
     #include <ws2tcpip.h>

     #pragma comment (lib, "ws2_32.lib")

     void makeConnection(std::string addr, std::string msg, int port, argparser arguments) {
          WSAData wsaData;
          SOCKET client;
          struct sockaddr_in server;
          const char *sendBuf;
          char server_reply[BUFLEN];
          int recv_size;

          server.sin_addr.s_addr = inet_addr(addr.c_str());
          server.sin_family = AF_INET;
          server.sin_port = htons(port);

          if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
               throw std::runtime_error("Error creating Winsock error: " + WSAGetLastError());
          }

          if((client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
               throw std::runtime_error("Failed to create socket: " + WSAGetLastError());
          }

          if(connect(client, (struct sockaddr *)&server, sizeof(server)) < 0) {
               throw std::runtime_error("Failed to connect to server!");
          }

          std::cout << "Connected!" << std::endl;
          while (true) {
               std::cout << "> ";
               std::getline(std::cin, msg);

               if(arguments.get_base64_obfuscation()) {
                    msg = b64::b64_encode(msg);
               }

               sendBuf = msg.c_str();
               std::cout << "Sending: " << sendBuf << std::endl;

               if(send(client, sendBuf, sizeof(msg), 0) < 0) {
                    throw std::runtime_error("Failure to send a message");
               }

               if((recv_size = recv(client, server_reply, BUFLEN, 0)) == SOCKET_ERROR) {
                    throw std::runtime_error("Recv failed!");
               }
               server_reply[recv_size] = '\0';
               if(arguments.get_base64_obfuscation()) {
                         std::string temp = b64::b64_decode((std::string)server_reply);
                         temp.copy(server_reply, temp.size()+1);
                         server_reply[temp.size()] = '\0';
                    }
               std::cout << "Server Replied: " << server_reply << std::endl;

               break; // remove this to keep a back and forth with server
          }
          closesocket(client);
          WSACleanup();
     }

     void server(int port, argparser arguments) {
          WSAData wsaData;
          SOCKET s, new_socket;
          struct sockaddr_in server, client;
          int c, recv_size;
          const char *message = "200 OK";
          char server_reply[BUFLEN] = {'0'};

          server.sin_addr.s_addr = INADDR_ANY;
          server.sin_family = AF_INET;
          server.sin_port = htons(port);

          if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
               throw std::runtime_error("Error creating Winsock error: " + WSAGetLastError());
          }

          if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
               throw std::runtime_error("Failed to create socket: " + WSAGetLastError());
          }

          std::cout << "Binding to port: " << port << std::endl;
          if(bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
               throw std::runtime_error("Failed to bind: " + WSAGetLastError());
          }

          std::cout << "Listening for new connections" << std::endl;
          listen(s, 10);
          c = sizeof(struct sockaddr_in);
          
          while ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET) {
               std::cout << "Connection received" << std::endl;
               while(true) {
                    if((recv_size = recv(new_socket, server_reply, BUFLEN, 0)) == SOCKET_ERROR) {
                         throw std::runtime_error("Recv failed!");
                    }
                    server_reply[recv_size] = '\0';

                    if(arguments.get_base64_obfuscation()) {
                         std::string temp = b64::b64_decode((std::string)server_reply);
                         temp.copy(server_reply, temp.size()+1);
                         server_reply[temp.size()] = '\0';
                         std::cout << "Client sent: " << server_reply << std::endl;

                         message = b64::b64_encode(message).c_str();
                         if(send(new_socket, message, sizeof(message), 0) < 0) {
                              throw std::runtime_error("Failure to send message");
                         }
                    }
                    else {
                         std::cout << "Client sent: " << server_reply << std::endl;

                         if(send(new_socket, message, sizeof(message), 0) < 0) {
                              throw std::runtime_error("Failure to send message");
                         }
                    }
                    
                    break; // remove this to keep a back and forth with connected client
               }
               break; // remove this to keep server running forever
               }

          if(new_socket == INVALID_SOCKET) {
               throw std::runtime_error("Failed to accept connection: " + WSAGetLastError());
          }

          closesocket(s);
          WSACleanup();
     }

     #endif

}
