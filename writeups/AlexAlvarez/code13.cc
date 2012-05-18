int n, l;

void shuffle(vector<int>& v) {
    int i = l - 1, j = n - 1;
    vector<int> aux;
    while (i >= 0 and j >= l) {
        aux.push_back(v[i]);
        aux.push_back(v[j]);
        --i; --j;
    }
    while (i >= 0) aux.push_back(v[i--]);
    while (j >= l) aux.push_back(v[j--]);
    v = aux;
}

BI mcm(BI& a, BI& b) {
    BI c, d = a;
    c.mcd(a, b);
    d /= c;
    d *= b;
    return d;
}

int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        cin >> n >> l;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = i;
        shuffle(v);
        vector<bool> vist(n, false);
        BI res = 1;
        for (int i = 0; i < n; ++i) {
            if (not vist[i]) {
                vist[i] = true;
                int len = 1, x = i;
                while (not vist[v[x]]) {
                    vist[v[x]] = true;
                    x = v[x];
                    ++len;
                }
                BI len2 = len;
                res = mcm(res, len2);
            }
        }
        cout << "Case #" << cas << ": " << res << endl;
    }
}