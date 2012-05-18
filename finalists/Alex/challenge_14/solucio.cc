#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;

string codifica(string s) {
    string res;
    int p = 1;
    for (int i = 0; i < s.size(); ++p) {
        if (__builtin_popcount(p) == 1) res += ".";
        else res += s[i++];
    }
    p = 1;
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] == '.') {
            int j = i, par = 0;
            while (j < res.size()) {
                for (int k = 0; k < p and k + j < res.size(); ++k) if (res[j + k] == '1') par = 1 - par;
                j += 2*p;
            }
            if (par) res[i] = '1';
            else res[i] = '0';
            p <<= 1;
        }
    }
    return res;
}

string decodifica(string s) {
    string r;
    for (int i = 0; i < s.size(); ++i) if (__builtin_popcount(i + 1) != 1) r += s[i];
    string res = codifica(r);
    int pos = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (__builtin_popcount(i + 1) == 1 and s[i] != res[i]) {
            pos += i + 1;
        }
    }
    if (pos != 0) s[pos - 1] = (s[pos - 1] == '0') ? '1' : '0';
    r = "";
    for (int i = 0; i < s.size(); ++i) if (__builtin_popcount(i + 1) != 1) r += s[i];
    return r;
}

char f(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        res *= 2;
        if (s[i] == '1') ++res;
    }
    return char(res);
}

int main() {
    string s;
    while (cin >> s) {
        if (s.size()%7 != 0) cout << "Error!";
        else {
            string r, res;
            bool ok = true;
            for (int i = 0; i < s.size(); i += 7) {
                r += decodifica(s.substr(i, min(7, int(s.size()) - i)));
                if (r.size() == 8) {
                    res += f(r);
                    if (r[0] == '1') ok = false;
                    r = "";
                }
            }
            if (ok) cout << res;
            else cout << "Error!";
        }
        cout << endl;
    }
}