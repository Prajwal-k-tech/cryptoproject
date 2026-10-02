#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
using namespace std;
//string to hex is pretty simple, take the ascii value of each char, take the lower nibble and the higher nibble,
string byteToHex(unsigned char byte) {
    const char hexDigits[] = "0123456789abcdef";
    string hex;
    hex += hexDigits[(byte >> 4) & 15];  // High nibble
    hex += hexDigits[byte & 15];         // Low nibble
    return hex;
}

string step3Encode(const string& input) {
    string hexString;
    for (char c : input) {
        hexString += byteToHex(static_cast<unsigned char>(c));
    }
    return hexString;
}

// Hex Decode
unsigned char hexToByte(const string& hex) {
    return static_cast<unsigned char>(stoi(hex, nullptr, 16));  // Convert hex to byte
}

string step2decode(const string& hexString) {
    if (hexString.size() % 2 != 0) {
        throw invalid_argument("Hexadecimal input must contain complete byte pairs.");
    }
    for (unsigned char c : hexString) {
        if (!isxdigit(c)) throw invalid_argument("Invalid hexadecimal character.");
    }
    string output;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        string hexPair = hexString.substr(i, 2);
        output += static_cast<char>(hexToByte(hexPair));
    }
    return output;
}
