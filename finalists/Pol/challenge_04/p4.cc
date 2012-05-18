#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> Vi;
typedef vector<ll> Vll;


int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    ll R, K;  // rounds, karts
    int G;    // groups
    cin >> R >> K >> G;
    
    Vll V(2*G); // people in each group
    for (int i = 0; i < G; ++i) cin >> V[i];
    for (int i = 0; i < G; ++i) V[G + i] = V[i];  // let's duplicate V just to simplify things
    
    Vi S(G);  // S[i]: maximum number of consecutive groups starting with the i-th that can run together
    Vll F(G); // F[i]: ammount of fuel that groups starting with the i-th one need to run
    {
      int j = 0;
      ll s = 0;
      for (int i = 0; i < G; ++i) {
        while (j - i < G and s + V[j] <= K) s += V[j++];
        S[i] = j - i;
        F[i] = s;
        s -= V[i];
      }
    }
    
    int cycle_start, cycle_size;  // size of the cycle, start of the cycle
    Vi cycle;                     // the cycle itself
    {
      Vi C(G, -1); // C[i] is the position of the i-th state in the cycle, where the i-th state is the state where the i-th group is at the front
      int c = 0;
      int p = 0;
      while (C[p] == -1) {
        C[p] = c++;
        p = (p + S[p])%G;
      }
      cycle_start = C[p];
      cycle_size = c - cycle_start;
      cycle = Vi(cycle_size);
      for (int i = 0; i < cycle_size; ++i) {
        cycle[i] = p;
        p = (p + S[p])%G;
      }
    }
    
    ll res = 0;
    {
      int p = 0;
      for (int i = 0; i < R and i < cycle_start; ++i) {
        res += F[p];
        p = (p + S[p])%G;
      }
    }
    
    if (R > cycle_start) {
      ll cycle_fuel = 0;
      for (int i = 0; i < cycle_size; ++i) cycle_fuel += F[cycle[i]];
      res += ((R - cycle_start)/cycle_size)*cycle_fuel;
      int m = (R - cycle_start)%cycle_size;
      for (int i = 0; i < m; ++i) res += F[cycle[i]];
    }
    
    cout << res << endl;
  }
}
