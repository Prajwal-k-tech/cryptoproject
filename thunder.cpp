#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
string step2(string ciphertext) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 32, 43, 55, 65, 73, 143, 144, 148, 150, 164, 165, 169, 170, 189, 193, 194, 195, 199, 202, 203, 204, 205, 208};
    string add = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string output;
    int input = 0, added = 0,pepperthun = 0;
    int len = ciphertext.size();

    for (int i = 0; pepperthun < sizeof(arr) / sizeof(arr[0]) && arr[pepperthun] < len; i++) {
        if (arr[pepperthun] == i) {
            added = rand() % add.size();  // Obfuscation only; not cryptographic randomness
            output += add[added];
            pepperthun++;
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

// Thunder Decrypt
string step3decrypt(string pepperd) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 32, 43, 55, 65, 73, 143, 144, 148, 150, 164, 165, 169, 170, 189, 193, 194, 195, 199, 202, 203, 204, 205, 208};
    int len = pepperd.length();
    int min = 0,pepperthun = 0;
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        if(arr[i] < len) {
            pepperthun++;
        } else {
            break;
        }
    }
    int pep = 0;
    string output;

    for (int i = 0; i < len; i++) {
        if (pep < pepperthun && i == arr[pep]) {
            pep++;  // Skip the added random character
            continue;
        }
        output += pepperd[i];
    }

    return output;
}
// int main(){
//     string input;
//     getline(cin, input);
//     string encrypted = thunder(input);
//     cout << encrypted << endl;
//     cout << thunderdecrypt(encrypted) << endl;
// }
