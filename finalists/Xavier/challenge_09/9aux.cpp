#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

#define x first
#define y second

typedef pair<int, pair<int,int> > page;
typedef vector<int> vi;

string code(int i) {
  stringstream lin;
  lin << setw(4) << setfill('0') << i;
  string res;
  lin >> res;
  return res;
}

int main() {
    map<string,vi > dict;
  
    for (int i = 1; i <= 800; ++i) {
      string name = "../documents/" + code(i);
      fstream fin(name.c_str(), fstream::in);
      cerr << name << endl;
      string s;
      int line = 0;
      while (getline(fin,s)) {
	line++;
	stringstream lin(s);
	int word = 0;
	while (lin >> s) {
	  ++word;
	  for (int j = 0; j < (signed)s.size(); ++j) s[j] = tolower(s[j]);
	  if (dict.find(s) == dict.end()) {
	    dict[s] = vi(800,0);	    
	  }
	  dict[s][i-1]++;
	}
      }      
      fin.close();
    }
    cout << dict.size() << endl;
    int i = 0;
    //for (map<string,vi>::iterator it = dict.begin(); it != dict.end(); ++it) cout << " " << it->first; cout << endl;
    for (map<string,vi>::iterator it = dict.begin(); it != dict.end(); ++it) {
	if ((++i)%1000 == 0) cerr << i << endl;
	cout << it->first << " ";
	for (int i = 0; i < (signed) it->second.size(); ++i) {
	    cout << " " << it->second[i];
	}
	cout << endl;
    }
}