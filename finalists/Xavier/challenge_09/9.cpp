#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

//9aux generates an index of documents
//9aux2 generates an index of the index

string code(int i) {
  stringstream lin;
  lin << setw(4) << setfill('0') << i;
  string res;
  lin >> res;
  return res;
}

void lookForWord(int document, string& myword, int k) {
  string name = "../documents/" + code(document);
  fstream fin(name.c_str(), fstream::in);
  string s;
  int line = 0;
  int times = 0;
  while (getline(fin,s)) {
    line++;
    stringstream lin(s);
    int word = 0;
    while (lin >> s) {
      ++word;
      for (int j = 0; j < (signed)s.size(); ++j) s[j] = tolower(s[j]);
      if (s == myword) {
	++times;
	if (times == k) {
	    cout << document << "-" << line << "-" << word << endl;
	    fin.close();
	    return;
	}
      }      
    }
  }      
}

int main() {
    fstream dict("total", fstream::in);
    fstream index("indextotal", fstream::in);
    map<string,int> ind;
    int n;
    index >> n;
    for (int i = 0; i < n; ++i) {
      string a; index >> a;
      int t; index >> t;
      ind[a] = t;
    }
    int c; cin >> c;
    while (c--) {
	string s; int t;
	cin >> s >> t;
	vector<int> v(800);
	//cerr << "I have to read from " << ind[s] << endl;
	dict.seekg(ind[s],ios_base::beg);
	string s2;
	dict >> s2;
	for (int i = 0; i < 800; ++i)
	    dict >> v[i];
	
	int acum = 0;
	for (int i = 0; i < 800; ++i)  {
	    if (acum <= t and t <= acum + v[i]) {
		//cerr << "I have to read documetn " << i + 1 << " " << acum << " " << v[i]  << endl;
		lookForWord(i+1,s,t - acum);
		break;
	    }    
	    acum += v[i];
	}
    } 
}