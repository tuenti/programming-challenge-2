#include <iostream>
#include <vector>
using namespace std;

#define MOD(x,n) (((x) < (n)) ? (x) : ((x)%(n)))

typedef long long ll;

//Calculo la solucion en O(G) con un precalculo en tiempo O(GlogG)
void solve(ll r, ll k, vector<ll>& v) {
    int n = v.size();
    
    //Precalculo on O(GlogG) para cada disposicion de la fila cuantos grupos entran
    vector<ll> S(2*n + 1, 0), qtt(n);
    for (int i = 1; i <= 2*n; ++i) S[i] = S[i - 1] + v[MOD(i - 1, n)];
    for (int i = 0; i < n; ++i) {
        //Binaria para encontrar el punto exacto
        int ini = i, fin = i + n - 1;
        while (ini <= fin) {
            int m = (ini + fin)/2;
            ll x = S[m + 1] - S[i];
            if (x <= k) ini = m + 1;
            else fin = m - 1;
        }
        qtt[i] = ini - i;
    }

    //Busco un ciclo dentro de la secuencia
    ll r2 = 0, res = 0;
    vector<ll> races(n, -1); //Cuantas carreras lleva el grupo i la primera vez que se pone el primero
    vector<ll> litros(n, -1); //Lo mismo para los litros
    int act = 0;
    while (r2 < r and races[act] < 0) {
        races[act] = r2;
        litros[act] = res;
        res += S[act + qtt[act]] - S[act];
        ++r2;
        act = MOD(act + qtt[act], n);
    }
    if (r2 < r) {
        ll len = r2 - races[act]; //Longitud del ciclo
        ll veces = (r - r2)/len; //Cuanto lo puedo repetir
        ll gasto = res - litros[act]; //Gasolina del ciclo
        r2 += (veces*len);
        res += (veces*gasto);
        while (r2 < r) { //El resto lo itero, sera menor que G el numero de iteraciones
            res += S[act + qtt[act]] - S[act];
            ++r2;
            act = MOD(act + qtt[act], n);
        }
    }
    cout << res << endl;
}

int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        ll r, k;
        int n;
        cin >> r >> k >> n;
        vector<ll> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        solve(r, k, v);
    }
}