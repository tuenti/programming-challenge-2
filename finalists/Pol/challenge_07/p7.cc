#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef set<int> SET;
typedef vector<char> Vc;

// dependencies
Vc dep[256];
SET depset[256];

Vc chr;
SET chrset;

int N;
char usat[256];
string tmp;

void genera(int n) {
  if (n == N) {
    cout << tmp << endl;
    return;
  }
  
  for (int i = 0; i < N; ++i) {
    int c = int(chr[i]);
    if (not usat[c]) {
      bool ok = true;
      for (int j = 0; ok and j < int(dep[c].size()); ++j)
        if (not usat[int(dep[c][j])]) ok = false;
      if (ok) {
        usat[c] = true;
        tmp[n] = c;
        genera(n + 1);
        usat[c] = false;
      }
    }
  }
}

int main() {
  string s;
  while (cin >> s) {
    int n = s.size();
    for (int i = 0; i < n; ++i) chrset.insert(s[i]);
    for (int i = 1; i < n; ++i) depset[int(s[i])].insert(s[i - 1]);
  }
  
  chr = Vc(chrset.begin(), chrset.end());
  
  for (int i = 0; i < 256; ++i)
    dep[i] = Vc(depset[i].begin(), depset[i].end());
  
  N = chr.size();
  for (int i = 0; i < 256; ++i) usat[i] = 0;  // this line is unnecessary
  tmp = string(N, '.');
  genera(0);
}
