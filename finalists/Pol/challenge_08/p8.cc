#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <openssl/md5.h>
using namespace std;

typedef vector<string> Vs;
typedef vector<Vs> Ms;

MD5_CTX sh;
unsigned char buff[20];

int N;
Ms M;

Ms dp;

void genera(int n, int c) {
  if (dp[n][c].size()) return;
  if (n == N) {
    dp[n][c] = string(1, c);
    return;
  }
  if (M[n][c].size() == 0) {
    genera(n + 1, c);
    dp[n][c] = dp[n + 1][c];
    return;
  }
  int sz = M[n][c].size();
  for (int i = 0; i < sz; ++i) {
    genera(n + 1, M[n][c][i]);
    dp[n][c] += dp[n + 1][M[n][c][i]];
  }
}

int main() {
  string ini;
  cin >> ini;
  
  string line;
  getline(cin, line);
  
  N = 0;
  while (getline(cin, line)) {
    M.push_back(Vs(256));
    int sz = line.size();
    int p = 0;
    while (p < sz) {
      int c = line[p];
      p += 3;
      while (p < sz and line[p] != ',') M[N][c] += line[p++];
      ++p;
    }
    ++N;
  }
  
  MD5_Init(&sh);
  
  dp = Ms(N + 1, Vs(256));
  for (int i = 0; i < int(ini.size()); ++i) {
    genera(0, ini[i]);
    MD5_Update(&sh, dp[0][ini[i]].c_str(), dp[0][ini[i]].size());
  }
  
  MD5_Final(buff, &sh);
  for (int i = 0; i < 16; ++i) printf("%02x", buff[i]);
  printf("\n");
}
