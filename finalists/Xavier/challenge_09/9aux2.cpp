#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

int main() {/*
  fstream in("prova.txt", fstream::in);
  cout << in.tellg() << endl;
  string s;
  in >> s;
  cout << in.tellg() << endl;
  in >> s;
  cout << in.tellg() << endl;
  */
  
  fstream in("total", fstream::in);
  string s;
  int n; in >> n;
  getline(in,s);
  cerr << n << endl;
  cout << n << endl;
  for (int i = 0; i < n; ++i) {
      //if ((i%1000)==0) cerr << i << endl;
      int t = in.tellg();
      string word;
      in >> s;
      cout << s << " " << t << " ";
      getline(in,s);    
  }
}