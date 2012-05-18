#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    ll W, H, CT;
    cin >> W >> H >> CT;
    
    string line;
    getline(cin, line);
    getline(cin, line);
    
    vector<int> v;
    stringstream ss(line);
    string s;
    while (ss >> s) v.push_back(s.size());
    int n = v.size();
    
    int m = 0;
    for (int i = 0; i < n; ++i)
      m = max(m, v[i]);
    
    ll esq = 1, dre = (W*CT)/m, res = 0;
    while (esq <= dre) {
      ll mig = (esq + dre)/2;
      ll rmax = (H*CT)/mig, cmax = (W*CT)/mig;
      
      int r = 1, c = 0;
      for (int i = 0; i < n; ++i) {
        if (c + v[i] > cmax) {
          ++r;
          c = 0;
        }
        c += v[i] + 1;
      }
      
      if (r > rmax) dre = mig - 1;
      else {
        res = mig;
        esq = mig + 1;
      }
    }
    
    int sum = 0;
    for (int i = 0; i < n; ++i)
      sum += v[i];
    
    cout << "Case #" << cas << ": " << (sum*res*res + 2*CT - 1)/(2*CT) << endl;
  }
}
