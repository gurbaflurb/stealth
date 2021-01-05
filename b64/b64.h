#ifndef __B64__
#define __B64__

namespace b64 {
    
    /**
     * Encodes input into a base64 string
     * 
     * @param string is the input string for either a file name or just regular plaintext
     * @return Base64 encoded string
     */
    std::string b64_encode(std::string);

    /**
     * Decodes input from a base64 string
     * 
     * @param string is the input base64 string
     * @return String object containing the decoded information that should be treated as raw binary
     */
    std::string b64_decode(std::string);

    /**
     * Encodes file 
     * @note WARNING, USE b64_encode INSTEAD OF THIS FUNCTION FOR PROPER USAGE
     * 
     * @param string File to be encoded
     * @return Base64 encoded string
     */
    std::string b64_file_encode(std::string);

    /**
     * Encodes input string 
     * @note WARNING, USE b64_encode INSTEAD OF THIS FUNCTION FOR PROPER USAGE
     * 
     * @param string input to be encoded
     * @return Base64 encoded string
     */
    std::string b64_input_encode(std::string);

    /**
     * Shifts binary of a character down by a set amount
     * 
     * @param char Character of 8 bits to be shifted down
     * @param int Amount to shift down by
     * @return Character of 8 bits shifted
     */
    char b64_shift_down(char, int);

    /**
     * Shifts binary of a character up by a set amount
     * 
     * @param char Character of 8 bits to be shifted up
     * @param int Amount to shift down by
     * @return Character of 8 bits shifted
     */
    char b64_shift_up(char, int);

    /**
     * Returns the base64 encoded charcater based on an 8 bit character from a base64 string
     * @note WARNING, this member function expects the 8 bit character input to already be shifted down to correctly return a character. Otherwise it will raise an exception.
     * 
     * @param char character to be found in base64 table
     * @return correct base64 encoded character
     */
    char b64_get_decoded_binary(char);

}

#endif