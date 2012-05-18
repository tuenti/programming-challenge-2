typedef long long ll;

inline ll g(ll y, ll m, ll d) {
    m = (m + 9)%12;
    y = y - m/10;
    return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);
}

inline int days(int y1, int m1, int d1, int y2, int m2, int d2) {
    return g(y2, m2, d2) - g(y1, m1, d1);
}