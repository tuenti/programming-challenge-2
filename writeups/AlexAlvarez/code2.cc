#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef unsigned long long ull;

const int INF = 1000000000;
int M[70][2];
string bin;

string to_binary(ull x) {
    string s;
    do {
        s += char('0' + (x&1));
        x >>= 1;
    } while (x > 0);
    return s;
}

int dp(int p, int c) {
    if (p == bin.size()) return (c == 0) ? 0 : -INF;
    int &ans = M[p][c];
    if (ans == -1) {
        if ((bin[p] == '1' and c == 1) or (bin[p] == '0' and c == 0)) 
            ans = max(2 + dp(p + 1, 1), dp(p + 1, 0));
        else if (bin[p] == '1' and c == 0) ans = 1 + dp(p + 1, 0);
        else ans = 1 + dp(p + 1, 1);
    }
    return ans;
}

int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        ull n;
        cin >> n;
        bin = to_binary(n);
        memset(M, -1, sizeof(M));
        cout << "Case #" << cas << ": " << dp(0, 0) << endl;
    }
}