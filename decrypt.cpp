#include <iostream>
#include <string>
#include <vector>
#include "hex.cpp"
#include "base64.cpp"
#include "prime.cpp"
#include "thunder.cpp"

using namespace std;
int main(){
    string input,step1,step2,step3dec,step4dec;
    getline(cin, input);
    try {
    step1=step1decrypt(input);
    step2=step2decode(step1);
    step3dec=step3decrypt(step2);
    step4dec=step4decode(step3dec);
    cout << step4dec;
    } catch (const exception& error) {
        cerr << error.what() << endl;
        return 1;
    }
}
