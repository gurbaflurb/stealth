# stealth

Tool I built to exfiltrate data to a remote server.

- Custom base64 encoder and decoder to assist in obfuscation.

- Custom socket programming using port 80 and fake web traffic headers to pretend to be normal web traffic.

- Custom argument parser to dynamically set values.

- Added [Cryptopp](https://github.com/weidai11/cryptopp) for encrypting communications

  

Building stealth should be easy as:

-  `make`

-  `make linux` or `make windows`
