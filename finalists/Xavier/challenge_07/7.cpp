#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;

vvi graf;

void generateAllTopologicalSortings(int current[], int pre[], set<int>& free, int i, int n, vc& translation) {
  if (i == n) {
      for (int j = 0; j < n; ++j) cout << translation[current[j]]; cout << endl;
      return;
  }
  int avail[free.size()];
  int k = 0;
  for (set<int>::iterator it = free.begin(); it != free.end(); ++it) avail[k++] = (*it);
  
  for (int k = 0; k < free.size(); ++k) {
    int u = avail[k];
    free.erase(u);
    for (int j = 0; j < graf[u].size(); ++j) {
      int v = graf[u][j];
      pre[v]--;
      if (pre[v] == 0) free.insert(v);
    }
    current[i] = u;
    generateAllTopologicalSortings(current, pre, free, i+1, n, translation);
    
    free.insert(u);    
    for (int j = 0; j < graf[u].size(); ++j) {
      int v = graf[u][j];
      if (pre[v] == 0) free.erase(v);
      pre[v]++;
    }
  }
}

map<char,int> dict;
int getid(char c) {
  if (dict.find(c) == dict.end()) {
    int n = dict.size();
    dict[c] = n;
    graf.push_back(vi(0));
  }
  return dict[c];
}

int main() {
  string s;
  while (cin >> s) {
     for(int i = 0; i < s.size() - 1; ++i)
	graf[getid(s[i])].push_back(getid(s[i+1]));
  }
  vc translation(dict.size());
  for (map<char,int>::iterator it = dict.begin(); it != dict.end(); ++it) 
    translation[it->second] = it->first;
//  cerr << "translation "; for (int i = 0; i < dict.size(); ++i) cerr << translation[i] << " "; cerr << endl;
  int current[dict.size()];
  int pre[dict.size()];
  for (int i = 0; i < dict.size(); ++i) pre[i] = 0;
  for (int i = 0; i < graf.size(); ++i) 
    for (int j = 0; j < graf[i].size(); ++j) {
      int v = graf[i][j];
      ++pre[v];
    }
//    cerr << "pre "; for (int i = 0; i < dict.size(); ++i) cerr << pre[i] << " "; cerr << endl;
  set<int> free;
  for (int i = 0; i < dict.size(); ++i) if (pre[i] == 0) free.insert(i);
  generateAllTopologicalSortings(current, pre, free, 0, dict.size(), translation);    
  
}
    