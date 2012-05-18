#include <openssl/md5.h>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;


int main() {
  string s, text;
  getline(cin,text);
  
  vector<string> v;
  while (getline(cin,s)) v.push_back(s);
  
  vvs graf(v.size(), vs(128, ""));
  for (int i = 0; i < (signed)v.size(); ++i) 
    for (int j = 0; j < 128; ++j)
      graf[i][j] = j;
    
  for (int i = 0; i < (signed)v.size(); ++i) {
    int state = 0; //0; u, 1: = 2; vs
    char u = 0;
    for (int j = 0; j < (signed)v[i].size(); ++j) {
      if (('a' <= v[i][j] and v[i][j] <= 'z') or ('A' <= v[i][j] and v[i][j] <= 'Z')) {
	if (state == 0) {
	  u = v[i][j];
	  graf[i][(unsigned int) u] = "";
	  state = 1;
	} 
	if (state == 2) graf[i][(unsigned int) u] += v[i][j];
      } if (v[i][j] == '=' and state == 1) state = 2;
      if (v[i][j] == ',' and state == 2) state = 0;
    }
  }
  string M[graf.size()][128];
  for (int i = 0; i < 128; ++i) M[graf.size() -1][i] = graf.back()[i];
  for (int i = (signed)graf.size() - 2; i >= 0; --i) {
      for (int j = 0; j < 128; ++j) {
	M[i][j] = "";
	for (int k = 0; k < (signed)graf[i][j].size(); ++k) {
	  M[i][j] += M[i+1][(unsigned int)graf[i][j][k]];
	}
      }
  }
  
  MD5_CTX md;
  MD5_Init(&md);
  
  for (int i = 0; i < (signed)text.size(); ++i) {
    MD5_Update(&md,M[0][(unsigned int)text[i]].c_str(), M[0][(unsigned int)text[i]].size());
  }
  

  unsigned char res[16];
  MD5_Final(res, &md);
  
  for (int i = 0; i < 16; ++i) printf("%02x", res[i]);
  printf("\n");
}