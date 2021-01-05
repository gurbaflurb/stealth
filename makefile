compile:
	@echo "compiling libraries"
	g++ -c net/network.cpp -o net/network.o
	g++ -c b64/b64.cpp -o b64/b64.o
	g++ -c argparser/argparser.cpp -o argparser/argparser.o
	(cd ./cryptopp && make)

windows:
	@echo "compiling server and client for windows"
	g++ server.cpp b64/*.o net/*.o argparser/*.o -Lcryptopp -l:libcryptopp.a -lws2_32 -Wall -o server.exe
	g++ client.cpp -static b64/*.o net/*.o argparser/*.o -Lcryptopp -l:libcryptopp.a -lws2_32 -Wall -o client.exe

linux:
	@echo "compiling server and client for linux"
	g++ server.cpp b64/*.o net/*.o argparser/*.o -Lcryptopp -l:libcryptopp.a -Wall -o server
	g++ client.cpp -static b64/*.o net/*.o argparser/*.o -Lcryptopp -l:libcryptopp.a -Wall -o client
