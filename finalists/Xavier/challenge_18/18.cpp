#include <iostream>
using namespace std;

int main() {
    int cas; cin >> cas;
    for (int i = 1; i <= cas; ++i) {
      unsigned long long a;
      cin >> a;
      cout << "Case #" << i << ": " << (a*(a + 1ll)/2ll + 1ll) << endl;
    }
}