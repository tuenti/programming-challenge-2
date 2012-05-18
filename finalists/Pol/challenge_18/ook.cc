#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> prog;
  
  ifstream f("program.bee", ifstream::in);
  string a, b;
  while (f >> a >> b) prog.push_back(a.substr(3, 1) + b.substr(3, 1));
  f.close();
  
  int n = prog.size();
  
  vector<int> match(n, -1);
  stack<int> st;
  for (int i = 0; i < n; ++i) {
    if (prog[i] == "!?") st.push(i);
    else if (prog[i] == "?!") {
      match[st.top()] = i;
      match[i] = st.top();
      st.pop();
    }
  }
  
  map<int, int> memo;
  int mp = 0;
  
  int pc = 0;
  while (pc < n) {
    if (prog[pc] == ".?") {
      ++mp;
      ++pc;
    }
    else if (prog[pc] == "?.") {
      --mp;
      ++pc;
    }
    else if (prog[pc] == "..") {
      ++memo[mp];
      ++pc;
    }
    else if (prog[pc] == "!!") {
      --memo[mp];
      ++pc;
    }
    else if (prog[pc] == ".!") {
      char c;
      if (cin >> c) memo[mp] = c;
      else memo[mp] = 0;
      ++pc;
    }
    else if (prog[pc] == "!.") {
      cout << char(memo[mp]);
      ++pc;
    }
    else if (prog[pc] == "!?") {
      if (memo[mp] == 0) pc = match[pc] + 1;
      else ++pc;
    }
    else if (prog[pc] == "?!") {
      if (memo[mp] != 0) pc = match[pc] + 1;
      else ++pc;
    }
    else {
      cerr << "FAIL" << endl;
      return 0;
    }
  }
  
  cout << endl;
}
