#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int nextLine(const vector<int>& v, const vector<int>& s, int cur, int space) {
    int i = cur, j = v.size()-1, bestSolution = cur;
    while (i <= j) {
      int m = (i + j)/2;
      //cerr << "binaria 2 " << i << " " << j << " " << m << " " << (s[m] - ((cur == 0)?0:s[cur-1])) << endl;
      if ((s[m] - ((cur == 0)?0:s[cur-1]) + m - cur) <= space) {
	bestSolution = m;
	i = m + 1;
	//cerr << "entro 2 " << i << endl;
      } else j = m - 1;
    }
    return bestSolution + 1;
}

bool puc(const vector<int>& v, const vector<int> & s, int w, int h, int m) {
    int lines = 0;
    int cur = 0;
    while (cur < v.size()) {
      ++lines;
      //cout << "it " << cur << " " << lines << endl;
      if (v[cur] > w/m) return false;
      cur = nextLine(v, s, cur, w/m);
    }
    return lines <= h/m; 
}

int main() {
    int c; cin >>c;
    int cas = 1;
    while (c--) {
      int w,h,ct; cin >> w >> h >> ct;
      string s; getline(cin,s); getline(cin,s);
      vector<int> v;
      stringstream lin(s);
      while (lin >> s) v.push_back(s.size());  
      //cout << "reading finished" << endl;
      vector<int> sl(v.size());
      sl[0] = v[0]; for (int i = 1; i < v.size(); ++i) sl[i] = v[i] + sl[i-1];
      w *= ct;
      h *= ct;
      int i = 1, j = h, bestSolution = 1;
      while (i <= j) {
	int m = (i + j)/2;
	//cerr << "binaria 1 " << i << " " << j << " " << m << endl;
	if (puc(v,sl,w,h,m)) {	  
	  //cerr << "puc 1 " << endl;
	  i = m+1;
	  bestSolution = m;
	} else j = m-1;
      }
      //cout << "font " << bestSolution << endl;
      int sum = 0;
      for (int i = 0; i < v.size(); ++i) sum += v[i];
      cout << "Case #"<< cas++ << ": " << (int)ceil(((double(bestSolution)*bestSolution/2)/ct)*sum) << endl;
    }
}