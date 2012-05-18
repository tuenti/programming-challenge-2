#include <iostream>
using namespace std;

string key1 = "a541714a17804ac281e6ddda5b707952";
string key2 = "ed8ce15da9b7b5e2ee70634cc235e363";
string key3 = "62cd275989e78ee56a81f0265a87562e";

string T = "0123456789abcdef";

int f(char c) {
    if (isdigit(c)) return c - '0';
    return c - 'a' + 10;
}

int main() {
    string input, res;
    cin >> input;
    for (int i = 0; i < input.size(); ++i) 
        if (isalpha(input[i])) input[i] = tolower(input[i]);
    for (int i = 0; i < key1.size(); ++i) {
        int x = (f(key1[i]) + f(key2[i]) + f(key3[i]) + f(input[i]))%16;
        res += T[x];
    }
    cout << res << endl;
}
