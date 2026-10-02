#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;

string step4decode(const string& input) {
    const string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    unordered_map<char, int> base64Index;
    for (int i = 0; i < base64Chars.size(); ++i) {
        base64Index[base64Chars[i]] = i;
    }

    string decoded;
    unsigned int buffer = 0;
    int bitsCollected = 0;
    for (char c : input) {
        if (c == '=') {
            break;
        }
        const auto found = base64Index.find(c);
        if (found == base64Index.end()) throw invalid_argument("Invalid Base64 character.");
        buffer = (buffer << 6) | found->second;
        bitsCollected += 6;

        while (bitsCollected >= 8) {
            bitsCollected -= 8;
            decoded += static_cast<char>((buffer >> bitsCollected) & 0xFF);
        }
    }

    return decoded;
}

// Base64 Encode
string step1Encode(const string& input) {
    const string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    string encoded;
    vector<unsigned char> bytes(input.begin(), input.end());

    for (size_t i = 0; i < bytes.size(); i += 3) {
        unsigned int buffer = 0;
        int padding = 0;

        for (size_t j = 0; j < 3; ++j) {
            if (i + j < bytes.size()) {
                buffer |= static_cast<unsigned int>(bytes[i + j]) << (16 - j * 8);
            } else {
                padding++;
            }
        }

        for (int j = 0; j < 4 - padding; ++j) {
            encoded += base64Chars[(buffer >> (18 - j * 6)) & 0x3F];
        }
        while (padding-- > 0) {
            encoded += '=';
        }
    }

    return encoded;
}

// int main() {
//     string original_text = "My favorite reindeer is (Dasher, Dancer, Prancer, Vixen, Comet, Cupid, Donner, or Rudolph).";
//     string encoded_text = base64Encode(original_text);
//     cout << "Original text: " << original_text << endl;
//     cout << "Encoded text: " << encoded_text << endl;
//     string decoded_text = base64Decode(encoded_text);
//     cout << "Decoded text: " << decoded_text << endl;
//     return 0;
// }
