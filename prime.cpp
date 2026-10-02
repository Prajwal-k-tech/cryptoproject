#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

string step4(string ciphertext) {
    int arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        arr[i]=arr[i]-1;
    }
    string add = "0123456789abcdef";
    string output;
    int pepper =0,input = 0, added = 0;
    int len = ciphertext.size();

    for (int i = 0; pepper < sizeof(arr) / sizeof(arr[0]) && arr[pepper] < len; i++) {
        if (arr[pepper] == i) {
            added = rand() % 16;
            output += add[added];
            pepper++;
            len++;
        } else {
            output += ciphertext[input++];
        }
    }

    while (input < ciphertext.size()) {
        output += ciphertext[input++];
    }

    return output;
}

// Prime Decrypt
string step1decrypt(string pepperd) {
    int arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
        arr[i] = arr[i]-1;
    }

    int len = pepperd.length();

    // Count how many positions from arr[] were used during encryption
    int pepper = 0;
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        if(arr[i] < len) {
            pepper++;
        } else {
            break;
        }
    }
    int pep = 0;
    int input_pos = 0;  // Track position in the original text
    string output;

    for (int i = 0; i < len; i++) {
        if (pep < pepper && i == arr[pep]) {
            pep++;  // Skip the random character
            continue;
        } else {
            output += pepperd[i];
            input_pos++;
        }
    }

    return output;
}
// int main(){
//     string input;
//     getline(cin, input);
//     string encrypted = prime(input);
//     cout << encrypted << endl;
//     cout << primedecrypt(encrypted) << endl;
// }
