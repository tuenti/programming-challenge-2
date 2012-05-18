#include <iostream>
using namespace std;

#define neg(c) ((c=='0')?'1':'0')

int mcd(int a, int b) {
  return (b==0)?a:mcd(b,a%b);
}

//input must be like "01010100010010101011001010101111"
string generalHammingCoder(string& info) {
  string res;
  int p = 1;
  for (int i = 0; i < (signed)info.size(); ++p) {
    if (__builtin_popcount(p) == 1) res += "$";
    else res += info[i++];
  }
  for (int i = 0; i < (signed)res.size(); ++i) 
    if (res[i] == '$') {
      int parsum = 0;
      for (int j = 0; j < (signed) res.size(); ++j)
        parsum += (((i+1)&(j+1))==(i+1))*(res[j] - '0');
      res[i] = (parsum%2 != 0)?'0':'1';
    }
  return res;
}

string generalHammingDecoder(string& received) {
  int sum = 0;
  for (int i = 0; i < (signed)received.size(); ++i) 
    if (__builtin_popcount(i+1) == 1) {
      int parsum = 0;
      for (int j = i+1; j < (signed)received.size(); ++j) {
        parsum += (((i+1)&(j+1))==(i+1))*(received[j] - '0');
      }
      if ((parsum%2) != (received[i] - '0')) sum += i+1;
    }
  if (sum != 0) {
    received[sum-1] = neg(received[sum-1]);
  }
  string res = "";
  for (int i = 0; i < (signed)received.size(); ++i) 
    if (__builtin_popcount(i+1) != 1) 
      res += received[i];
  return res;
}

string cod(int a) {
  return (a==0)?"0":"1";
}

string hum74decode(string& s) {
    string res = "";
    for (int i = 0; i < (signed)s.size(); i += 7) {
      string aux = s.substr(i, 7);
      res += generalHammingDecoder(aux);
    }
    return res;
}

#define num(c) (c - '0')

int pot[] = {1,2,4,8,16,32,64,128};

int main() {
    string s;
    while (getline(cin,s)) {
      if ((s.size()%14) != 0) {
        cout << "Error!" << endl;
        continue;
      }
      string r = hum74decode(s);
      string res = "";
      bool error = 0;
      for (int i = 0; i < r.size(); i+=8) {
          if (num(r[i])==1) error = 1;
          char a = 0;
          for (int j = 0; j < 8; ++j) a += pot[7 - j]*num(r[i+j]);
          res += a;
      }
      if (error) cout << "Error!" << endl;
      else cout << res << endl;
    }
}