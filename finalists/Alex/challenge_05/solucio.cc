#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const ll DIF_DIA = 2255477;

int palos[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
string repre[] = {"xxxxxxo", "oxxoooo", "xxoxxox", "xxxxoox", "oxxooxx", "xoxxoxx", "xoxxxxx", "xxxoooo", "xxxxxxx", "xxxxoxx"};

inline ll segundos(int h, int m, int s) {
    return h*3600 + m*60 + s;
}

inline ll g(ll y, ll m, ll d) {
    m = (m + 9)%12;
    y = y - m/10;
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);
}

//Calcula la diferencia en dias menos 1
inline int dias(int y1, int m1, int d1, int y2, int m2, int d2) {
    return g(y2, m2, d2) - g(y1, m1, d1) - 1;
}

//Total de palos iluminados
inline ll total(int h, int m, int s) {
    return palos[h%10] + palos[h/10] + palos[m%10] + palos[m/10] + palos[s%10] + palos[s/10];
}

//Itera n segundos en el viejo
ll itera_viejo(int h, int m, int s, int n) {
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        ++s;
        if (s == 60) {
            s = 0;
            ++m;
        }
        if (m == 60) {
            m = 0;
            ++h;
        }
        if (h == 24) h = 0;
        res += total(h, m, s);
    }
    return res;
}

ll dist(string& s, string& r) {
    ll res = 0;
    for (int i = 0; i < 7; ++i) if (s[i] == 'x' and r[i] == 'o') ++res;
    return res;
}

inline ll diff(int nuevo, int viejo) {
    return dist(repre[nuevo%10], repre[viejo%10]) + dist(repre[nuevo/10], repre[viejo/10]);
}

//Itera n segundos en el nuevo
ll itera_nuevo(int h, int m, int s, int n) {
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int hh = h, mm = m, ss = s;
        ++s;
        if (s == 60) {
            s = 0;
            ++m;
        }
        if (m == 60) {
            m = 0;
            ++h;
        }
        if (h == 24) h = 0;
        res += diff(h, hh) + diff(m, mm) + diff(s, ss);
    }
    return res;
}

int main() {
    cout.sync_with_stdio();
    int y1, m1, d1, y2, m2, d2;
    int hora1, min1, seg1, hora2, min2, seg2;
    char c;
    while (cin >> y1 >> c >> m1 >> c >> d1 >> c >> hora1 >> c >> min1 >> c >> seg1 >> c >> y2 >> c >> m2 >> c >> d2 >> hora2 >> c >> min2 >> c >> seg2) {
        if (y1 == y2 and m1 == m2 and d1 == d2) {
            int s = segundos(hora2, min2, seg2) - segundos(hora1, min1, seg1);
            cout << itera_viejo(hora1, min1, seg1, s) - itera_nuevo(hora1, min1, seg1, s) << endl;
        }
        else {
            int s = segundos(hora2, min2, seg2);
            int res = itera_viejo(0,0,0, s) - itera_nuevo(0, 0, 0, s);
            s = 3600*24 - segundos(hora1, min1, seg1);
            res += itera_viejo(hora1, min1, seg1, s) - itera_nuevo(hora1, min1, seg1, s);
            res += DIF_DIA*dias(y1, m1, d1, y2, m2, d2);
            cout << res << endl;
        }
    }
}