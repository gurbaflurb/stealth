#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include "b64.h"

namespace b64 {
    char base64Lookup[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                             'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                             'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 
                             'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                             'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
                             'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', '+', '/'};

    std::string b64_encode(std::string msg){
        std::string encoded;
        try {
            encoded = b64_file_encode(msg);
        }
        catch(const std::exception& e) {
            encoded = b64_input_encode(msg);
        }
        return encoded;
    }

    std::string b64_decode(std::string encoded) {
        std::string decoded = "";
        char c0, c1, c2, c3;
        char s1, s2;

        if(encoded.length() % 4 != 0) {
            throw std::runtime_error("Input length doesn't conform to base64 standards!");
        } else {
            for (int i = 0; i < (int)encoded.length(); i+=4) {
                c0 = b64_get_decoded_binary(encoded[i]);
                c1 = b64_get_decoded_binary(encoded[i+1]);
                c2 = b64_get_decoded_binary(encoded[i+2]);
                c3 = b64_get_decoded_binary(encoded[i+3]);

                if(c2 == -1 && c3 == -1) {
                    s1 = c1 & 0b00110000;
                    decoded += (char)((c0 << 2)+(s1 >> 4));

                } else if (c3 == -1) {
                    s1 = c1 & 0b00110000;
                    s2 = c2 & 0b00000011;
                    decoded += (char)((c0 << 2)+(s1 >> 4));
                    decoded += (char)((c1 << 4)+(c2 >> 2));
                    
                } else {
                    s1 = c1 & 0b00110000;
                    s2 = c2 & 0b00000011;
                    decoded += (char)((c0 << 2)+(s1 >> 4));
                    decoded += (char)((c1 << 4)+(c2 >> 2));
                    decoded += (char)((c3)+(s2 << 6));
                }
            }
        }
        return decoded;
    }

    std::string b64_file_encode(std::string fileName) {
        std::ifstream file(fileName, std::ios::in | std::ios::binary);
        std::string encoded;
        
        if(file.is_open()){
            char c;
            int leftOver = 0, tempLeftOver = 0;
            int count = 0;
            while(file.read(&c, 1)) {
                char currentChar = c;
                switch (count)
                {
                case 0:
                    tempLeftOver = currentChar & 0b00000011;
                    currentChar = b64_shift_down(currentChar, 2); 
                    break;
                case 1:
                    tempLeftOver = currentChar & 0b00001111;
                    currentChar = b64_shift_down(currentChar, 4);
                    leftOver = b64_shift_up(leftOver, 4);
                    currentChar += leftOver;
                    break;
                case 2:
                    tempLeftOver = currentChar & 0b00111111;
                    currentChar = b64_shift_down(currentChar, 6);
                    leftOver = b64_shift_up(leftOver, 2);
                    currentChar += leftOver;
                    break;
                }
                encoded += b64::base64Lookup[(int)currentChar];
                if(count == 2){
                    encoded += b64::base64Lookup[(int)tempLeftOver];
                }
                leftOver = tempLeftOver;
                tempLeftOver = 0;
                count = (count + 1) % 3;
            }
            if(count == 1) {
                leftOver = b64_shift_up(leftOver, 4);
                encoded += b64::base64Lookup[(int)leftOver];
                encoded += "==";
            }
            else if (count == 2) {
                leftOver = b64_shift_up(leftOver, 2);
                encoded += b64::base64Lookup[(int)leftOver];
                encoded += '=';
            }
        } else {
            throw std::invalid_argument("Failed to open file!");
        }
        file.close();
        return encoded;
    }

    std::string b64_input_encode(std::string msg) {
        std::string encoded;
        char currentChar;
        int leftOver = 0, tempLeftOver = 0;
        int count = 0;
        for(int i = 0; i < (int)msg.length(); i++) {
            currentChar = msg[i];
            switch (count)
            {
            case 0:
                tempLeftOver = currentChar & 0b00000011;
                currentChar = b64_shift_down(currentChar, 2); 
                break;
            case 1:
                tempLeftOver = currentChar & 0b00001111;
                currentChar = b64_shift_down(currentChar, 4);
                leftOver = b64_shift_up(leftOver, 4);
                currentChar += leftOver;
                break;
            case 2:
                tempLeftOver = currentChar & 0b00111111;
                currentChar = b64_shift_down(currentChar, 6);
                leftOver = b64_shift_up(leftOver, 2);
                currentChar += leftOver;
                break;
            }
            encoded += b64::base64Lookup[(int)currentChar];
            if(count == 2){
                encoded += b64::base64Lookup[(int)tempLeftOver];
            }
            leftOver = tempLeftOver;
            tempLeftOver = 0;
            count = (count + 1) % 3;
        }
        if(count == 1) {
            leftOver = b64_shift_up(leftOver, 4);
            encoded += b64::base64Lookup[(int)leftOver];
            encoded += "==";
        }
        else if (count == 2) {
            leftOver = b64_shift_up(leftOver, 2);
            encoded += b64::base64Lookup[(int)leftOver];
            encoded += '=';
        }
        return encoded;
    }

    char b64_shift_down(char binary, int shiftAmount) {
        for (int i = 0; i < shiftAmount; i++) {
            if(i == 0) {
                binary = (binary >> 1) & 0b01111111;
            }else {
                binary = (binary >> 1);
            }
        }
        return binary;
    }

    char b64_shift_up(char binary, int shiftAmount) {
        for (int i = 0; i < shiftAmount; i++) {
            if(i == 0) {
                binary = (binary << 1) & 0b11111110;
            }else {
                binary = (binary << 1);
            }
        }
        return binary;
    }

    char b64_get_decoded_binary(char currentLetter) {
        if(currentLetter == '=') {
            return -1;
        }
        int n = sizeof(base64Lookup)/sizeof(base64Lookup[0]);
        char return_char;
        auto index = std::find(base64Lookup, base64Lookup + n, currentLetter);
        if (index != std::end(base64Lookup)) {
            return_char = std::distance(base64Lookup, index);
        } else {
            throw std::invalid_argument("Invalid base64 string!");
        }
        return return_char;
    }

}