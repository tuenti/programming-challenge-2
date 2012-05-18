#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, string> P;
typedef vector<P> Vp;
typedef vector<int> Vi;

// 1 point: A E I L N O R S T U
// 2 points: D G
// 3 points: B C M P
// 4 points: F H V W Y
// 5 points: K
// 8 points: J X
// 10 points: Q Z
//                     A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
const int points[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3,10, 1, 1, 1, 1, 4, 4, 8, 4,10 };

int N;
Vp V;

bool sortf(const P& a, const P& b) {
  if (a.first != b.first) return a.first > b.first;
  return a.second < b.second;
}

int score(string s) {
  int res = 0;
  int n = s.size();
  for (int i = 0; i < n; ++i)
    res += points[s[i] - 'A'];
  return res;
}

void load_wordlist() {
  V.clear();
  ifstream f("descrambler_wordlist.txt", ifstream::in);
  string s;
  while (f >> s) V.push_back(P(score(s), s));
  f.close();
  N = V.size();
  sort(V.begin(), V.end(), sortf);
}

int main() {
  load_wordlist();
  
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    string R, B;
    cin >> R >> B;
    
    Vi vr(26, 0);
    for (int i = 0; i < int(R.size()); ++i) ++vr[R[i] - 'A'];
    
    Vi vb(26, 0);
    for (int i = 0; i < int(B.size()); ++i) ++vb[B[i] - 'A'];
    
    for (int i = 0; i < N; ++i) {
      Vi v(26, 0);
      int sz = V[i].second.size();
      for (int j = 0; j < sz; ++j) ++v[V[i].second[j] - 'A'];
      
      bool ok = false;
      for (int j = 0; not ok and j < 26; ++j)
        if (v[j] > 0 and vb[j] > 0)
          ok = true;
      
      int g = 0;
      for (int j = 0; ok and g < 2 and j < 26; ++j)
        if (v[j] > vr[j]) {
          if (vb[j] == 0 or v[j] != vr[j] + 1) ok = false;
          ++g;
        }
      
      if (ok and g < 2) {
        cout << V[i].second << " " << V[i].first << endl;
        break;
      }
    }
  }
}
