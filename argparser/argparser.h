#ifndef __ARGPARSE__
#define __ARGPARSE__

#include <iostream>
#include <cstdlib>

class argparser{
    private:
        std::string remoteHost;
        std::string program;
        bool base64_encode = false;
        bool verbose = false;
        bool fake_http_headers = false;
        int port = 80;

    public:
        argparser(int argc, char ** argv);

        void print_help();

        void set_port(int);
        int get_port();

        void set_remote_host(std::string);
        std::string get_remote_host();

        void set_verbose();
        bool get_verbose();

        void set_fake_http_headers();
        bool get_fake_http_headers();

        void set_base64_obfuscation();
        bool get_base64_obfuscation();

};

#endif
