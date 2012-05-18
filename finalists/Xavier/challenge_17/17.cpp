#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define abs(a)   (((a)>0)?(a):(-(a)))

typedef long double ld;

struct p2 {
  ld x,y;
  p2(){}
  p2(ld a, ld b) {x = a; y = b;}
};

typedef vector<p2> vp;
typedef vector<vp> vvp;
typedef vector<vvp> vvvp;

bool right(const p2& s1, const p2& s2, const p2& p) {
  return ((s2.x - s1.x)*(p.y - s1.y) - (s2.y - s1.y)*(p.x - s1.x)) >= 0;
}

//center, vertex, number of sides
void generateRegularPoligon(vector<p2>& p, const p2& c, const p2& v, int n) {
  p2 v1(v.x - c.x, v.y - c.y), v2(c.y - v.y, v.x - c.x);

  for (int i = 0; i < n; ++i) {
    ld angle = 2*M_PI*i/n;
    p.push_back(p2(c.x + v1.x*cos(angle) + v2.x*sin(angle), c.y + v1.y*cos(angle) + v2.y*sin(angle)));
  }
}

//return 1 if at right, 0 if at left, -1 if cut
int right(const p2& s1, const p2& s2, const vector<p2>& p) {
  bool atright = right(s1,s2,p[0]);
  for (int i = 0; i < (signed)p.size(); ++i)
    if (right(s1,s2,p[i]) != atright) return -1;
  return atright;
}

bool tryLine(const p2& s1, const p2& s2, const vvvp& ingres) {
  for (int i = 0; i < (signed)ingres.size(); ++i) {
    int sum1 = 0, sum2 = 0;
    for (int j = 0; j < (signed)ingres[i].size(); ++j) {
      int res = right(s1, s2, ingres[i][j]);
      if (res == 0) ++sum1;
      else if (res == 1) ++sum2;
      else return false;
    }
    if (sum1 != sum2) return false;      
  }
  return true;
}


int main() {  
  int cas = 1;
  int casos; cin >> casos;
  while (casos--) {
    p2 c; ld radius; int n;
    cin >> c.x >> c.y >> radius >> n;
    vvvp ingres(n);
    for (int i = 0; i < n; ++i) {
      string id; cin >> id;
      int costats, ni; cin >> costats >> ni;
      ingres[i] = vvp(ni);
      for (int j = 0; j < ni; ++j) {
          p2 cp, v;
          cin >> cp.x >> cp.y >> v.x >> v.y;
          generateRegularPoligon(ingres[i][j], cp, v, costats);
      }
    }
    
   bool puc = false;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < (signed)ingres[i].size(); ++j)
        for (int k = 0; k < (signed)ingres[i][j].size(); ++k) {
          if (tryLine(c, ingres[i][j][k], ingres)) puc = true;
        }
          
    cout << "Case #" << cas++ << ": " << ((puc)?"TRUE":"FALSE") << endl;
  }  
}



