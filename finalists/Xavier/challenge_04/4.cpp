#include <iostream>
#include <vector>
using namespace std;


//cost is max(g,r) * log g

long long suma(long long Sl[], long long Sr[], int current, int m, int g) {
  if (current + m < g) return Sl[current + m] - ((current==0)?0:Sl[current-1]);
  return Sr[current] + Sl[(current + m)%g];
}  

int nextCurrent(long long G[], long long Sl[], long long Sr[], int g, int current, long long k, long long& aux) {
  int i = 0, j = g - 1, bestSolution = -1;
  long long bestSum = 0;
  while (i <= j) {
      int m = (i+j)/2;
      long long auxSum = suma(Sl, Sr, current, m, g);
      //cerr << "I try " << i << " " << j << " " << m << " " << auxSum << endl;
      if (auxSum <= k and auxSum > bestSum) {
	//cerr << "good solution" << endl;
	bestSolution = (current + m + 1)%g;
	bestSum = auxSum;
	i = m + 1;
      } else j = m - 1;
  }
  //cerr << "Solution " << bestSolution << " " << bestSum << endl;
  aux = bestSum;
  return bestSolution;
}

int main() {
  int n; cin >> n;
  while (n--) {
    long long r, k;
    int g;
    cin >> r >> k >> g;
    if (k != 0 and g != 0) {
      long long G[g];
      for (int i = 0; i < g; ++i) cin >> G[i];
      long long Sl[g], Sr[g];
      Sl[0] = G[0]; Sr[g-1] = G[g-1];
      for (int i = 1; i < g; ++i) Sl[i] = G[i] + Sl[i-1];
      for (int i = g-2; i >= 0; --i) Sr[i] = G[i] + Sr[i+1];
      int current = 0, cr = 0;
      bool first = true, cicletrobat = false;
      long long gasoil = 0;
      while (cr < r) {
	if (!cicletrobat and !first and current == 0) {
	  gasoil *= r/cr;
	  cr = r - r%cr;
	  cicletrobat = true;
	} else {
	  //cerr << "curr " << current << " cr " << cr << " gasoil " << gasoil << endl;
	  first = false;
	  long long aux;
	  current = nextCurrent(G, Sl, Sr, g, current, k, aux);
	  gasoil += aux;
	  ++cr;
	}     
      }
      cout << gasoil << endl;
    }
    else cout << 0 << endl;
  }
}