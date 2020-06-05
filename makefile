gen:
	@echo "compiling and running"
	g++ -c b64/b64.cpp -o b64/b64.dll
	g++ main.cpp b64/*.dll -Wall -o main.exe
	
test:
	@echo "Running Tests:"
	./main.exe f
	@echo "Output should be: Zg=="
	./main.exe fo
	@echo "Output should be: Zm8="
	./main.exe foo
	@echo "Output should be: Zm9v"
	./main.exe foob
	@echo "Output should be: Zm9vYg=="
	./main.exe fooba
	@echo "Output should be: Zm9vYmE="
	./main.exe foobar
	@echo "Output should be: Zm9vYmFy"
	.\main.exe test.txt
	@echo "Output should be: TWFu"
	.\main.exe test1.txt
	@echo "Output should be: TWE="
	.\main.exe test2.txt
	@echo "Output should be: TQ=="
	.\main.exe Tree
	@echo "Output should be: VHJlZQ=="
	.\main.exe test3.txt
	@echo "Output should be: TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="
