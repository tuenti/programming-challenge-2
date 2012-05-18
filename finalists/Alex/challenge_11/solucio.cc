#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int qtt[30], qtt2[30], qtt3[30];
int p[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int puntos(string& s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) res += p[s[i] - 'A'];
    return res;
}

bool can(string& a) {
    memset(qtt3, 0, sizeof(qtt3));
    for (int i = 0; i < a.size(); ++i) ++qtt3[a[i] - 'A'];
    bool usat = false, puc_usar = false;
    for (int i = 0; i < 30; ++i) {
        if (qtt3[i] > qtt[i]) {
            if (qtt3[i] == qtt[i] + 1 and qtt2[i] > 0 and not usat) {
                usat = true;
                puc_usar = true;
            }
            else return false;
        }
        else {
            if (qtt2[i] > 0) puc_usar = true;
        }
    }
    if (puc_usar) return true;
    return false;
}

//Para cada palabra del diccionario, cuento cuantas letras tiene de cada tipo y miro si la puedo generar con las que tengo
//Tiempo O(|diccionario|)
int main() {
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        ifstream fin("/home/alex/codigos/tuenti/Challenge11/descrambler_wordlist.txt");
        string s, r, w;
        cin >> s >> r;
        memset(qtt, 0, sizeof(qtt));
        memset(qtt2, 0, sizeof(qtt2));
        for (int i = 0; i < s.size(); ++i) ++qtt[s[i] - 'A'];
        for (int i = 0; i < r.size(); ++i) ++qtt2[r[i] - 'A'];
        int best = 0;
        string res;
        while (getline(fin, w)) {
            if (can(w)) {
                int punts = puntos(w);
                if (punts > best) {
                    best = punts;
                    res = w;
                }
            }
        }
        fin.close();
        cout << res << " " << best << endl;
    }
}