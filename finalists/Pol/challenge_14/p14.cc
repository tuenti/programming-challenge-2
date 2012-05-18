#include <iostream>
#include <string>
using namespace std;

// What is "readable"???
// I consider "readable" the characters between ' ' and '~' (inclusive) in ASCII.

const int M[7][4] = {
  { 1, 1, 0, 1 },
  { 1, 0, 1, 1 },
  { 1, 0, 0, 0 },
  { 0, 1, 1, 1 },
  { 0, 1, 0, 0 },
  { 0, 0, 1, 0 },
  { 0, 0, 0, 1 }
};

int hamming[128];

int dist(int a, int b) {
  int res = 0;
  for (int i = 0; i < 8; ++i)
    if (((a>>i)&1) != ((b>>i)&1)) ++res;
  return res;
}

int encode(int n) {
  int vec[4];
  for (int i = 0; i < 4; ++i) vec[4 - 1 - i] = (n>>i)&1;
  
  int res[7];
  for (int i = 0; i < 7; ++i) {
    res[i] = 0;
    for (int j = 0; j < 4; ++j)
      res[i] += M[i][j]*vec[j];
  }
  
  int r = 0;
  for (int i = 0; i < 7; ++i) r |= (res[7 - 1 - i]&1)<<i;
  return r;
}

void compute_hamming() {
  for (int i = 0; i < (1<<4); ++i) {
    int t = encode(i);
    for (int j = 0; j < 128; ++j)
      if (dist(t, j) < 2) hamming[j] = i;
  }
}

int main() {
  compute_hamming();
  
  string s;
  while (cin >> s) {
    int n = s.size();
    if (n%14 != 0) {
      cout << "Error!" << endl;
      continue;
    }
    
    bool ok = true;
    string res;
    for (int i = 0; i < n; i += 14) {
      int t1 = 0, t2 = 0;
      for (int j = 0; j < 7; ++j) t1 = 2*t1 + s[i + j] - '0';
      for (int j = 0; j < 7; ++j) t2 = 2*t2 + s[i + 7 + j] - '0';
      
      int r = (hamming[t1]<<4) | hamming[t2];
      if (' ' <= r and r <= '~') res += char(r);
      else {
        ok = false;
        break;
      }
    }
    
    if (ok) cout << res << endl;
    else cout << "Error!" << endl;
  }
}
