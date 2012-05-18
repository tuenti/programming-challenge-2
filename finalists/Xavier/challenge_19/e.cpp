#include <iostream>
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
    for (int i = 0; i < r.size(); i += 4) {
      int num = r[i]*8 + r[i+1]*4 + r[i+2]*2 + r[i+3] - 15*'0';
      if (0 <= num and num <= 9) s += num + '0';
      else s += num - 10 + 'a';
    }
    return s;
}

int numHexToDec(char a) {
  if ('0' <= a and a <= '9') return a - '0';
  else return a - 'a' + 10;
}

ll pot(int i) {
  ll s = 1;
  for (int j = 0; j < i; ++j) s *= 16;
  return s;
}

ll hexToInteger(const string& r, int j) {
  ll sum = 0;
  for (int i = 0; i < 8; ++i) 
    sum += ll(numHexToDec(r[j + i]))*pot(7 - i);
  return sum;
}
  
string D[] = {"10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", 
	      "11101", "11110", "11111", "00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001",
	      "01010", "01011", "01100", "01101", "01110", "01111"};

string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int invBase64_chars(char a) {
    if ('A' <= a and a <= 'Z') return a - 'A';
    if ('a' <= a and a <= 'z') return a - 'a' + 26;
    return a - '0' + 52;
}

string asciiToBinary(char a) {
  string res = "";
  for (int i = 7; i >= 0; --i) res += ((a>>i)&1) + '0';
  return res;
}

int pot2[] = {1,2,4,8,16,32,64,128,256,512,1024};

char binaryToChar(const string& r) {
  char a = 0;
  for (int i = 0; i < r.size(); ++i) 
    a += (r[i] - '0')*pot2[7 - i];
  return a;
}

int binaryToInteger(const string& r) {
    int sum = 0;
    for (int i = 0; i < r.size(); ++i) 
      sum += (r[i] - '0')*pot2[r.size() - 1 - i];
    return sum;
}

string integerToBinary(int a) {
  string res = "";
  for (int i = 5; i >= 0; --i) res += ((a>>i)&1) + '0';
  return res;
}

string base64_code(const string& r) {
    string res = "";
    for (int i = 0; i + 3 < r.size(); i += 3) {
      string aux = asciiToBinary(r[i]) + asciiToBinary(r[i+1]) + asciiToBinary(r[i+2]);
      for (int j = 0; j < aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    if (r.size()%3 == 1) {
      string aux = asciiToBinary(r[r.size() -1]) + "0000";
      for (int j = 0; j < aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    if (r.size()%3 == 2) {
      string aux = asciiToBinary(r[r.size() -2]) + asciiToBinary(r[r.size() -2]) + "00";
      for (int j = 0; j < aux.size(); j+=6) 
        res += base64_chars[binaryToInteger(aux.substr(j,6))];
    }
    return res;
}

string base64_decode(const string& r) {
  string res = "";
  for (int i = 0; i < r.size(); i += 4) {
    string aux = integerToBinary(invBase64_chars(r[i])) + 
                 integerToBinary(invBase64_chars(r[i + 1])) + 
                 integerToBinary(invBase64_chars(r[i + 2])) + 
                 integerToBinary(invBase64_chars(r[i + 3]));
    res += binaryToChar(aux.substr(0,8));
    res += binaryToChar(aux.substr(8,8));
    res += binaryToChar(aux.substr(16,8));
  }
  return res;    
}

int main() {
    string s;
    cin >> s;
    string s1 = base64_decode(s);

    string res = "";
    
    ll ant = 0;
    for (int i = 0; i < s1.size(); i += 8) {
      ll act = hexToInteger(s1, i);
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
