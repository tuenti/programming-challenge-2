#include <iostream>
#include <iomanip>
using namespace std;

typedef long long ll;

string BtH[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

string hexToBinary(const string& r) {
  string res = "";
  for (int i = 0; i < (signed) r.size(); ++i) {
    if ('0' <= r[i] and r[i] <= '9') res += BtH[r[i] - '0'];
    else res += BtH[r[i] - 'a' + 10];
  }
  return res;
}

string binaryToHex(const string& r) {
    string s = "";
    for (int i = 0; i < (signed) r.size(); i += 4) {
      int num = r[i]*8 + r[i+1]*4 + r[i+2]*2 + r[i+3] - 15*'0';
      if (0 <= num and num <= 9) s += num + '0';
      else s += num - 10 + 'a';
    }
    return s;
}

string integerToBinary(int a, int nbits) {
  string res = "";
  for (int i = nbits - 1; i >= 0; --i) res += ((a>>i)&1) + '0';
  return res;
}

int binaryToInteger(const string& r) {
  int sum = 0, pot = 1;
  for (int i = (signed)r.size() - 1; i >= 0; --i) {
    sum += (r[i] - '0')*pot;
    pot *= 2;
  }
  return sum;
}

ll hexToInteger(const string& a) {
  ll sum = 0, pot = 1;
  for (int i = (signed)a.size() - 1; i >= 0; --i) {
    sum += ll(('0' <= a[i] and a[i] <= '9')?a[i]-'0':a[i]-'a'+10)*pot;
    pot *= 16;
  }
  return sum;
}

string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int invBase64_chars(char a) {
    if ('A' <= a and a <= 'Z') return a - 'A';
    if ('a' <= a and a <= 'z') return a - 'a' + 26;
    return a - '0' + 52;
}

string base64_code(const string& r) {
    string res = "";
    for (int i = 0; i + 3 < (signed)r.size(); i += 3) {
      string aux = integerToBinary(r[i],8) + integerToBinary(r[i+1],8) + integerToBinary(r[i+2],8);
      for (int j = 0; j < (signed)aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    if (r.size()%3 == 1) {
      string aux = integerToBinary(r[r.size() -1], 8) + "0000";
      for (int j = 0; j < (signed)aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    if (r.size()%3 == 2) {
      string aux = integerToBinary(r[r.size() -2], 8) + integerToBinary(r[r.size() -1],8) + "00";
      for (int j = 0; j < (signed)aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    return res;
}

string base64_decode(const string& r) {
  string res = "";
  for (int i = 0; i < (signed)r.size(); i += 4) {
    string aux = integerToBinary(invBase64_chars(r[i]),6) + 
                 integerToBinary(invBase64_chars(r[i + 1]),6) + 
                 integerToBinary(invBase64_chars(r[i + 2]), 6) + 
                 integerToBinary(invBase64_chars(r[i + 3]), 6);
    res += char(binaryToInteger(aux.substr(0,8)));
    res += char(binaryToInteger(aux.substr(8,8)));
    res += char(binaryToInteger(aux.substr(16,8)));
  }
  return res;    
}

string D[] = {"10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", 
          "11101", "11110", "11111", "00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001",
          "01010", "01011", "01100", "01101", "01110", "01111"};

int main() {
    string s; cin >> s;
    string s1 = base64_decode(s);

    string res = "";
    
    ll ant = 0;
    for (int i = 0; i < (signed)s1.size(); i += 8) {
      ll act = hexToInteger(s1.substr(i,8));
      if (-16 <= act - ant and act - ant <= 15) 
        res += "0" + D[act - ant + 16];
      else 
        res += "1" + hexToBinary(s1.substr(i,8));
      ant = act;
    }
    while (res.size()%4 != 0) res += "0";
    string r2 = binaryToHex(res);
    cout << base64_code(r2) << endl; 
}
