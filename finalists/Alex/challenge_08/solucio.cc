#include <iostream>
#include <openssl/md5.h>
#include <vector>
#include <cstdio>
#include <sstream>
using namespace std;

#define DP(c,p) ((M[int(c)][p].size() == 0) ? dp(c,p) : M[int(c)][p])

string M[128][20];
unsigned char res[16];
vector<vector<string> > T;

vector<string> split(string& s) {
    for (int i = 0; i < int(s.size()); ++i) if (s[i] == ',') s[i] = ' ';
    stringstream ss(s);
    vector<string> ans(128);
    while (ss >> s) ans[int(s[0])] = s.substr(3, int(s.size()) - 3);
    return ans;
}

string dp(char c, int p) {
    if (p == int(T.size())) return string(1, c);
    if (M[int(c)][p].size() == 0) {
        if (T[p][int(c)].size() > 0) {
            for (int j = 0; j < int(T[p][int(c)].size()); ++j) M[int(c)][p] += DP(T[p][int(c)][j], p + 1);
        }
        else M[int(c)][p] = DP(c, p + 1);
    }
    return M[int(c)][p];
}

int main() {
    string s, r;
    getline(cin, s);
    while (getline(cin, r)) T.push_back(split(r));
    string aux;
    MD5_CTX md;
    MD5_Init(&md);
    
    //Precalculo en que se transforma cada caracter con una programacion dinamica
    for (int i = 0; i < 128; ++i) dp(char(i), 0);
    
    //Voy calculando el MD5 a trozos
    for (int i = 0; i < int(s.size()); ++i) MD5_Update(&md, M[int(s[i])][0].c_str(), M[int(s[i])][0].size());
    
    MD5_Final(res, &md);
    for (int i = 0; i < 16; ++i) printf("%02x", res[i]);
    printf("\n");
}