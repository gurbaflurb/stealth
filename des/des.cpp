#include "des.h"

desHandler::desHandler() {}

desHandler::desHandler(std::string initKey) {
    key = initKey;
}

desHandler::desHandler(std::string initKey, std::string msg) {
    key = initKey;
    is_encrypted = true;
    encrypt_msg_to_cipherText(msg);
}

std::string desHandler::run_cipher(std::string msg) {
    encrypt_msg_to_cipherText(msg);
}
