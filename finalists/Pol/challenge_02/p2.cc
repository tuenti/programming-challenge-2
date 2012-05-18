#include <iostream>
using namespace std;

typedef unsigned long long ull;

int popcount(ull n) {
  int res = 0;
  for (int i = 0; i < 64; ++i)
    if ((n>>i)&1) ++res;
  return res;
}

int result(ull n) {
  int t = 0;
  while (t < 63 and (1ULL<<(t + 1)) - 1 <= n) ++t;
  return t + popcount(n - ((1ULL<<t) - 1));
}

int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    ull n;
    cin >> n;
    cout << "Case #" << cas << ": " << result(n) << endl;
  }
}
