#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        ll n;
        cin >> n;
        cout << "Case #" << cas << ": " << n*(n + 1LL)/2LL + 1LL << endl;
    }
}