#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll mcd(ll a, ll b) {
  if (b == 0) return a;
  else return mcd(b, a%b);
}
ll mcm2(ll a, ll b) {
  return a/mcd(a,b)*b;
}

ll mcm(const vector<int>& moves) {
    ll res = 1;
    for (int i = 0; i < (signed)moves.size(); ++i) res = mcm2(res, moves[i]);
    return res; 
}

int nextPos(int cur, int n, int l) {
  if (l <= n/2) {
    if (cur < l) return 2*(l-1-cur);
    if (cur >= n - l) return 2*(n-1-cur) + 1;
    return n-1 - (cur - l);
  }
  else {
    int l2 = n - l;
    if (cur < l - l2) return n - 1 - cur;
    if (cur >= n - l2) return 2*(n - 1 - cur) + 1;
    return 2*(l - 1 - cur);
  }
}

ll number(int n, int l) {
    vector<int> moves(n,-1);
    vector<int> aux(n);
    for (int i = 0; i < n; ++i) 
      if (moves[i] == -1) {
	//cerr << "I try position " << i << endl;
	 int k = nextPos(i,n,l), cont = 1;
	 aux[0] = i;
	 while (k != i) {
	  // cerr << "   I am at " <<k << endl;
	   aux[cont] = k; ++cont;
	   k = nextPos(k,n,l);
	 }
	 for (int j = 0; j < cont; ++j)
	   moves[aux[j]] = cont;	 
      }
    return mcm(moves);
}

int main() {
    int c; cin >> c;
    int cas = 1;
    while (c--) {
      int n, l; cin >> n >> l;
      cout << "Case #" << cas++ << ": " << number(n,l) << endl;
    }
}