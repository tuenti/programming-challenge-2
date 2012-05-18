#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ll minim, best = 0;
    int posminim = 0, posmaxim = 0, posminimact = 0, i = 1;
    cin >> minim;
    ll x;
    while (cin >> x) {
        if (x - minim > best) {
            best = x - minim;
            posminim = posminimact;
            posmaxim = i;
        }
        if (minim > x) {
            minim = x;
            posminimact = i;
        }
        ++i;
    }
    cout << posminim*100 << " " << posmaxim*100 << " " << best << endl; 
}