#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

double EPS = 1e-6;

//Miro si puedo poner fuente n
bool check(int w, int h, vector<string>& v, int n) {
    if (n == 0) return true;
    int lines = h/n;
    if (lines == 0) return false;
    int linia = 0, ch = 0, i = 0;
    while (i < v.size()) {
        int x = v[i].size();
        if (ch > 0) ++x;
        if ((x + ch)*n <= w) {
            ch += x;
            ++i;
        }
        else {
            if (ch == 0) return false;
            else {
                ch = 0;
                ++linia;
                if (linia == lines) return false;
            }
        }
    }
    return true;
}

int main() {
    int casos;
    cin >> casos;
    for (int z = 1; z <= casos; ++z) {
        cout << "Case #" << z << ": ";
        int w, h, count;
        cin >> w >> h >> count;
        w *= count;
        h *= count;
        string s, r;
        vector<string> v;
        getline(cin, s);
        getline(cin, s);
        r = s;
        stringstream ss(s);
        while (ss >> s) v.push_back(s);

        
        //Binaria sobre la fuente
        int ini = 0, fin = min(w, h);
        while (ini <= fin) {
            int m = (ini + fin)/2;
            if (check(w, h, v, m)) ini = m + 1;
            else fin = m - 1;
        }

        //Calculo cuanto hilo necesito con esa fuente.
        double res = 0, qtt = (ini - 1)*(ini - 1)/2.0/double(count);
        for (int i = 0; i < r.size(); ++i) {
            if (r[i] != ' ') res += qtt;
        }
        cout << int(res + 1 - EPS) << endl;
    }
}