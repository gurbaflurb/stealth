#include <time.h>
#include "des.h"

desHandler::desHandler() {
    key = generate_key();
}

desHandler::desHandler(std::string initKey) {
    if(initKey.length() != 8) {
        throw std::runtime_error("Invalid key!");
    }
    key = initKey;
}

std::string desHandler::padMsg(std::string msg) {
    return msg += '\0'*(64-(msg.length() % 64));
}

std::string desHandler::run_cipher(std::string msg) {
    // run DES on the passed in msg
    std::string fixedMsg = padMsg(msg);
    std::string encryptedMsg = "";

    // loop through 64 bit chunks (which is 8 characters given plaintext)
    for(int i = 0; i < fixedMsg.length(); i+= 8) {
        // create the two halves C0 and D0 by using pc1_left for C0 and pc1_Right for D0
        std::string c0 = "";
        std::string d0 = "";
        
    }
    
    return "";
}

std::string desHandler::generate_key() {
    std::string newKey = "";
    std::srand(time(NULL));
    
    for(int i = 0; i < 64; i++) {
        char temp = rand() % 256;
        newKey += temp;
    }
    
    return newKey;
}

std::string desHandler::run_DES(std::string msg) {
    return run_cipher(msg);
}