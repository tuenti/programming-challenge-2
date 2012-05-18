#include <iostream>
using namespace std;

int hex(char a) {
  if ('a' <= a and a <= 'f') return a - 'a' + 10;
  if ('A' <= a and a <= 'F') return a - 'A' + 10;
  else return a - '0';
}

int main() {
  char key1[] = "ed8ce15da9b7b5e2ee70634cc235e363";
  char key2[] = "a541714a17804ac281e6ddda5b707952";
  char key3[] = "62cd275989e78ee56a81f0265a87562e";
  string s;
  cin >> s;
  for (int i = 0; i < (signed) s.size(); ++i) {
      int num1 = hex(key1[i]);
      int num2 = hex(key2[i]);
      int num3 = hex(key3[i]);
      int num4 = hex(s[i]);
      cout << hex << (num1 + num2 + num3 + num4)%16;
  }
  cout << endl;
}