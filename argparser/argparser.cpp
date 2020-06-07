#include "argparser.h"

argparser::argparser(int argc, char ** argv) {
    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "-h" || arg == "--help"){
            print_help();
            exit(0);
        }
        else if(arg == "-b" || arg == "--base64") {
            set_base64_obfuscation();
        }
        else if(arg == "-f" || arg == "--fake-http-headers") {
            set_fake_http_headers();
        }
        else if(arg == "-p" || arg == "--port"){
            set_port(std::stoi(argv[i+1]));
        }
        else if(arg == "-v" || arg == "--verbose") {
            set_verbose();
        }
        else if(arg == "-r" || arg == "--remote") {
            set_remote_host(argv[i+1]);
        }
        
    }
    program = argv[0];

}

void argparser::print_help() {
    std::cout << "Usage: " << program << "<bfpv> <settings>\n"
    << "Options:\n"
    << "\t-h, --help\t\tPrint this menu and quit\n"
    << "\t-p, --port\t\tSet the port the remote server is listening on\n"
    << "\t-v, --verbose\t\tSet verbosity\n"
    << "\t-b, --base64\t\tSet data being exfiltraited to be encoded with base64\n"
    << "\t-f, --fake-http-headers\t\tAdd fake http headers to each message being sent\n"
    << "\t-r, --remote\t\tSet Remote server address" << std::endl;
}

void argparser::set_port(int newPort) {
    port = newPort;
}
int argparser::get_port() {
    return port;
}

void argparser::set_remote_host(std::string newRemoteHost) {
    remoteHost = newRemoteHost;
}
std::string argparser::get_remote_host() {
    return remoteHost;
}

void argparser::set_verbose() {
    verbose = true;
}
bool argparser::get_verbose() {
    return verbose;
}

void argparser::set_fake_http_headers() {
    fake_http_headers = true;
}
bool argparser::get_fake_http_headers() {
    return fake_http_headers;
}

void argparser::set_base64_obfuscation() {
    base64_encode = true;
}
bool argparser::get_base64_obfuscation() {
    return base64_encode;
}