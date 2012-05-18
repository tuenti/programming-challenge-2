#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll ant = 0;

//Hex to Bin
string toBin(ll x, int bits) {
    string s;
    do {
        if (x&1) s += "1";
        else s += "0";
        x >>=1;
    } while (--bits);
    reverse(s.begin(), s.end());
    return s;
}

inline int val2(char c) {
    if (isdigit(c)) return c - '0';
    return c - 'a' + 10;
}

ll val(string s) {
    ll res = 0;
    for (int i = 0; i < s.size(); ++i) {
        res <<= 4;
        res |= val2(s[i]);
    }
    return res;
}

string f(string s) {
    ll x = val(s);
    if (x - ant <= 15 and x - ant >= -16) {
        string aux = "0" + toBin(x - ant, 5);
        ant = x;
        return aux;
    }
    else {
        string aux = "1" + toBin(x, 32);
        ant = x;
        return aux;
    }
}

string toHex(string s) {
    if (s == "0000") return "0";
    if (s == "0001") return "1";
    if (s == "0010") return "2";
    if (s == "0011") return "3";
    if (s == "0100") return "4";
    if (s == "0101") return "5";
    if (s == "0110") return "6";
    if (s == "0111") return "7";
    if (s == "1000") return "8";
    if (s == "1001") return "9";
    if (s == "1010") return "a";
    if (s == "1011") return "b";
    if (s == "1100") return "c";
    if (s == "1101") return "d";
    if (s == "1110") return "e";
    return "f";
}

string T = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int num(char c) {
    for (int i = 0; i < 64; ++i) if (T[i] == c) return i;
    return 0;
}

string decode64(string& s) {
    string res;
    int i;
    for (i = 0; i < s.size(); i += 4) {
        if (s[i + 3] != '=') {
            int a = num(s[i]), b = num(s[i + 1]), c = num(s[i + 2]), d = num(s[i + 3]);
            ll x = (a << 18) | (b << 12) | (c << 6) | d;
            c = x&((1 << 8) - 1);
            x >>= 8;
            b = x&((1 << 8) - 1);
            x >>= 8;
            a = x&((1 << 8) - 1);
            res += char(a);
            res += char(b);
            res += char(c);
        }
        else if (s[i + 2] != '=') {
            int a = num(s[i]), b = num(s[i + 1]), c = num(s[i + 2]);
            ll x = (a << 12) | (b << 6) | c;
            x >>= 2;
            b = x&((1 << 8) - 1);
            x >>= 8;
            a = x&((1 << 8) - 1);
            res += char(a);
            res += char(b);
        }
        else {
            int a = num(s[i]), b = num(s[i + 1]);
            ll x = (a << 6) | b;
            x >>= 4;
            a = x&((1 << 8) - 1);
            res += char(a);
        }
    }
    return res;
}

string encode64(string& s) {
    string res;
    int i;
    for (i = 0; i + 3 <= s.size(); i += 3) {
        ll x = (int(s[i]) << 16) | (int(s[i + 1]) << 8) | int(s[i + 2]);
        int a, b, c, d;
        d = x&((1 << 6) - 1);
        x >>= 6;
        c = x&((1 << 6) - 1);
        x >>= 6;
        b = x&((1 << 6) - 1);
        x >>= 6;
        a = x&((1 << 6) - 1);
        res += T[a];
        res += T[b];
        res += T[c];
        res += T[d];
    }
    if (i + 1 == s.size()) {
        ll x = (int(s[i]) << 4);
        int a, b;
        b = x&((1 << 6) - 1);
        x >>= 6;
        a = x&((1 << 6) - 1);
        res += T[a];
        res += T[b];
    }
    else if (i + 2 == s.size()) {
        ll x = (int(s[i]) << 10) | (int(s[i + 1]) << 2);
        int a, b, c;
        c = x&((1 << 6) - 1);
        x >>= 6;
        b = x&((1 << 6) - 1);
        x >>= 6;
        a = x&((1 << 6) - 1);
        res += T[a];
        res += T[b];
        res += T[c];
    }
    return res;
}

int main() {
    string s, res;
    cin >> s;
    s = decode64(s);

    for (int i = 0; i < s.size(); i += 8) res += f(s.substr(i, min(int(s.size()) - i, 8)));

    string ans;
    while (res.size()%4 != 0) res += "0";
    for (int i = 0; i < res.size(); i += 4) {
        ans += toHex(res.substr(i, 4));        
    }
    cout << encode64(ans) << endl;
}