#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

typedef long long ll;

int dig(int x) {
    int res = 0;
    do {
        ++res;
        x /= 10;
    } while (x > 0);
    return res;
}

string str(int x) {
    stringstream ss;
    ss << x;
    string s;
    ss >> s;
    return s;
}

//Genera un archivo con todas las palabras y sus apariciones en los i primeros documentos
int main() {
    map<string, vector<ll> > v;
    for (int i = 1; i <= 800; ++i) {
        string nom = "documents/" + string(4 - dig(i), '0') + str(i);
        ifstream file(nom.c_str());
        string s;
        while (file >> s) {
            for (int j = 0; j < s.size(); ++j) {
                if (not (isdigit(s[j]) or isalpha(s[j]))) s[j] = ' ';
                if (isalpha(s[j])) s[j] = tolower(s[j]);
            }
            stringstream ss(s);
            while (ss >> s) {
                if (v[s].size() == 0) v[s].push_back(0);
                while (v[s].size() < i) v[s].push_back(v[s][v[s].size() - 1]);
                ++v[s][i - 1];
            }
        }
        cerr << i << endl;
        file.close();
    }
    for (map<string, vector<ll> >::iterator it = v.begin(); it != v.end(); ++it) {
        cout << it->first;
        for (int i = 0; i < (it->second).size(); ++i) cout << " " << (it->second)[i];
        cout << endl;
    }
}