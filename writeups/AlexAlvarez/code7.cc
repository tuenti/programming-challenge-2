#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

vector<char> alfa;
vector<string> res;
VVI G;
VI in;
    
//Genero todas las ordenaciones topologicas del arbol formado por
//un nodo para cada caracter y arista si aparece esa pareja en un subcode
//en ese orden
void rec(int p, list<int>& L, VI& sol) {
    if (p == sol.size()) {
        string s;
        for (int i = 0; i < sol.size(); ++i) s += alfa[sol[i]];
        res.push_back(s);
        return;
    }
    list<int> aux = L;
    for (list<int>::iterator it = L.begin(); it != L.end(); ++it) {
        int u = *it, qtt = 0;
        sol[p] = u;
        aux.pop_front();
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i];
            --in[v];
            if (in[v] == 0) {
                aux.push_back(v);
                ++qtt;
            }
        }
        rec(p + 1, aux, sol);
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i];
            ++in[v];
        }
        for (int i = 0; i < qtt; ++i) aux.pop_back();
        aux.push_back(u);
    }
}

int main() {
    string s;
    vector<string> v;
    map<char, int> id;
    while (cin >> s) {
        v.push_back(s);
        for (int i = 0; i < s.size(); ++i) {
            if (not id.count(s[i])) {
                id[s[i]] = G.size();
                alfa.push_back(s[i]);
                G.resize(G.size() + 1);
                in.push_back(0);
            }
            if (i > 0) {
                G[id[s[i - 1]]].push_back(id[s[i]]);
                ++in[id[s[i]]];
            }
        }
    }
    list<int> L;
    for (int i = 0; i < G.size(); ++i) if (in[i] == 0) L.push_back(i);
    VI sol(alfa.size());
    rec(0, L, sol);
    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); ++i) cout << res[i] << endl;
}