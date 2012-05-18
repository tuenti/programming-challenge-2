#include <iostream>
#include <string>
using namespace std;

const string H1 = "ed8ce15da9b7b5e2ee70634cc235e363"; // MD5(courage), from the QR
const string H2 = "a541714a17804ac281e6ddda5b707952"; // MD5(wisdom), from the metadata
const string H3 = "62cd275989e78ee56a81f0265a87562e"; // MD5(power), from "Power, Wisdom and Courage"

int todec(char c) {
  if ('0' <= c and c <= '9') return c - '0';
  if ('A' <= c and c <= 'Z') return 10 + c - 'A';
  return 10 + c - 'a';
}

char tohex(int n) {
  if (n < 10) return '0' + n;
  return 'a' + n - 10;
}

int main() {
  string S;
  cin >> S;
  
  for (int i = 0; i < 32; ++i)
    cout << tohex((todec(S[i]) + todec(H1[i]) + todec(H2[i]) + todec(H3[i]))%16);
  cout << endl;
}
