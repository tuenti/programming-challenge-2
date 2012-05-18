#include <iostream>
using namespace std;

int main() {
  int c; cin >> c;
  for (int j = 0; j < c; ++j){
    unsigned long long n;
    cin >> n;
    int sum = 0;
    unsigned long long pot = 1;
    while (((pot<<1) - 1) <= n) {sum++; pot <<= 1;}
    unsigned long long y = n - pot + 1;
    for (int i = 0; i < 64; ++i) if ((y>>i)&1 == 1) ++sum;
    cout << "Case #" << j+1 << ": " << sum <<  endl;
  }
}