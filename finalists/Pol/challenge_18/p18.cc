#include <iostream>
using namespace std;

//Input is the number of straight cuts made through a round chocolate cake and output is the maximum number of cake pieces that can be produced.

typedef long long ll;

int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    ll n;
    cin >> n;
    cout << "Case #" << cas << ": " << (n*n + n)/2 + 1 << endl;
  }
}
