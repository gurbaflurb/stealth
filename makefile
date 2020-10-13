windows:
	@echo "compiling server and client"
	g++ server.cpp b64/*.dll net/*.dll argparser/*.dll -lws2_32 -Wall -o server.exe
	g++ client.cpp -static b64/*.dll net/*.dll argparser/*.dll -lws2_32 -Wall -o client.exe

windows-all:
	@echo "re-compiling all files"
	g++ -c net/network.cpp -o net/network.dll
	g++ -c b64/b64.cpp -o b64/b64.dll
	g++ -c argparser/argparser.cpp -o argparser/argparser.dll
	g++ server.cpp b64/*.dll net/*.dll argparser/*.dll -lws2_32 -Wall -o server.exe
	g++ client.cpp -static b64/*.dll net/*.dll argparser/*.dll -lws2_32 -Wall -o client.exe

linux:
	@echo "compiling server and client"
	g++ server.cpp b64/*.o net/*.o argparser/*.o -Wall -o server
	g++ client.cpp -static b64/*.o net/*.o argparser/*.o -Wall -o client

linux-all:
	@echo "re-compiling all files"
	g++ -c net/network.cpp -o net/network.o
	g++ -c b64/b64.cpp -o b64/b64.o
	g++ -c argparser/argparser.cpp -o argparser/argparser.o
	g++ server.cpp b64/*.o net/*.o argparser/*.o -Wall -o server
	g++ client.cpp -static b64/*.o net/*.o argparser/*.o -Wall -o client
