#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Let's consider each vector of calls as an n-dimensional vector in the space.
// We can calculate the angle between 2 vectors in order to determine how "similar" they are. The closer
// the angle is, the more similar the vectors are.
// Given an unknown vector, if the most similar one to it among the known vectors is SAFE, then we conclude
// the unkown vector is SAFE, and the same with MALWARE.

typedef long double ld;
typedef long long ll;
typedef vector<ll> Vi;
typedef vector<Vi> Mi;
typedef vector<ld> Vd;
typedef vector<Vd> Md;
typedef vector<char> Vc;

void normalize(Vd& v) {
  int n = v.size();
  ld m = 0;
  for (int i = 0; i < n; ++i) m += v[i]*v[i];
  m = sqrt(m);
  for (int i = 0; i < n; ++i) v[i] /= m;
}

int main() {
  int R, U, N;
  cin >> R >> U >> N;
  
  Vc type(R);
  Mi vect(R, Vi(N));
  Md norm(R, Vd(N));
  for (int i = 0; i < R; ++i) {
    cin >> type[i];
    for (int j = 0; j < N; ++j) cin >> vect[i][j];
    for (int j = 0; j < N; ++j) norm[i][j] = vect[i][j];
    normalize(norm[i]);
  }
  
  ll res = 0;
  for (int i = 0; i < U; ++i) {
    Vi vec(N);
    for (int j = 0; j < N; ++j) cin >> vec[j];
    Vd nor(N);
    for (int j = 0; j < N; ++j) nor[j] = vec[j];
    normalize(nor);
    
    ld maxi = -1;
    char what = 'S';
    for (int j = 0; j < R; ++j) {
      ld t = 0;
      for (int k = 0; k < N; ++k)
        t += norm[j][k]*nor[k];
      if (t > maxi) {
        maxi = t;
        what = type[j];
      }
    }
    
    if (what == 'M') {
      for (int j = 0; j < N; ++j) res += vec[j];
    }
  }
  
  cout << res << endl;
}
