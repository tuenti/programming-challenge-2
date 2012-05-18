#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// For this problem, an O(n*logn) solution can be implemented, where n is the number of vertices.
// Given the small constraints in this case, I decided to go with a simplier O(n^2) solution.

#define PB push_back
#define X first
#define Y second

typedef long double ld;
typedef pair<ld, ld> P;
typedef vector<P> Vp;
typedef vector<Vp> Mp;
typedef vector<ld> Vd;

const ld EPS = 1e-9;

ld cross(P a, P b, P c) {
  return (c.X - b.X)*(a.Y - b.Y) - (c.Y - b.Y)*(a.X - b.X);
}

int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    ld cx, cy, rad;
    cin >> cx >> cy >> rad;
    
    Mp vert;
    {
      int n;
      cin >> n;
      for (int i = 0; i < n; ++i) {
        string spam;
        int e, m;
        cin >> spam >> e >> m;
        for (int j = 0; j < m; ++j) {
          ld px, py, vx, vy;
          cin >> px >> py >> vx >> vy;
          px -= cx;
          py -= cy;
          vx -= cx;
          vy -= cy;
          
          Vp v(e);
          ld dx = vx - px;
          ld dy = vy - py;
          ld a = atan2(dy, dx);
          ld d = sqrt(dx*dx + dy*dy);
          for (int k = 0; k < e; ++k) {
            ld x = px + d*cos(2*k*M_PI/e + a);
            ld y = py + d*sin(2*k*M_PI/e + a);
            v[k] = P(x, y);
          }
          vert.PB(v);
        }
      }
    }
    
    int n = vert.size();
    
//     cerr << "***" << endl;
//     for (int i = 0; i < n; ++i) {
//       for (int j = 0; j < int(vert[i].size()); ++j)
//         cerr << " (" << vert[i][j].X << ", " << vert[i][j].Y << ")";
//       cerr << endl;
//     }
    
    Vd angle;
    for (int i = 0; i < n; ++i) {
      int m = vert[i].size();
      for (int j = 0; j < m; ++j)
        angle.PB(atan2(vert[i][j].Y, vert[i][j].X));
    }
    
    bool ok = false;
    for (int a = 0; not ok and a < int(angle.size()); ++a) {
      ok = true;
      ld ang = angle[a];
      P p1(rad*cos(ang), rad*sin(ang));
      P p2(rad*cos(ang + M_PI), rad*sin(ang + M_PI));
      int c1 = 0, c2 = 0;
      for (int i = 0; ok and i < n; ++i) {
        int pos = 0, neg = 0;
        int m = vert[i].size();
        for (int j = 0; j < m; ++j) {
          ld t = cross(p1, vert[i][j], p2);
          if (t > EPS) ++pos;
          else if (t < -EPS) ++neg;
        }
        if (pos > 0 and neg > 0) ok = false;
        if (pos > 0) ++c1;
        else ++c2;
      }
      if (c1 != c2) ok = false;
    }
    
    cout << "Case #" << cas << ": ";
    if (ok) cout << "TRUE" << endl;
    else cout << "FALSE" << endl;
  }
}
