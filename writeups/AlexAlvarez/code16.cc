#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<double> VD;
typedef vector<VD> VVD;
const double EPS = 1e-6;

double norma(VD& v) {
    double res = 0;
    for (int i = 0; i < v.size(); ++i) res += (v[i]*v[i]);
    return sqrt(res);
}

double dist(VD& a, VD& b) {
    double res = 0;
    for (int i = 0; i < a.size(); ++i) res += ((a[i] - b[i])*(a[i] - b[i]));
    return sqrt(res);
}

//Agrupo malos y buenos y por cada proceso desconocido, 
//busco si esta en promedio mas cerca de los buenos o de los malos
int main() {
    int r, u, n;
    cin >> r >> u >> n;
    VVD S, M;
    for (int i = 0; i < r; ++i) {
        char c;
        cin >> c;
        VD v(n);
        for (int j = 0; j < n; ++j) cin >> v[j];
        double norm = norma(v);
        if (norm > EPS) for (int j = 0; j < n; ++j) v[j] /= norm;
        if (c == 'S') S.push_back(v);
        else M.push_back(v);
    }
    int res = 0;
    for (int i = 0; i < u; ++i) {
        VD v(n);
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            cin >> v[j];
            sum += v[j];
        }
        double norm = norma(v);
        if (norm > EPS) for (int j = 0; j < n; ++j) v[j] /= norm;
        double d1 = 0, d2 = 0;
        for (int j = 0; j < S.size(); ++j) d1 += (1.0/dist(v, S[j]));
        for (int j = 0; j < M.size(); ++j) d2 += (1.0/dist(v, M[j]));
        if (S.size() > 0) d1 /= double(S.size());
        if (M.size() > 0) d2 /= double(M.size());
        if (d1 < d2) res += sum;
    }
    cout << res << endl;
}