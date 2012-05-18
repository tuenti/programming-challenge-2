#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
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

//Busca la palabra n veces en el documento
void busca(string& s, ll n, int doc) {
    string nom = "/home/alex/codigos/tuenti/Challenge9/documents/" + string(4 - dig(doc), '0') + str(doc);
    ifstream fin(nom.c_str());
    string line;
    int linia = 1;
    
    //Busco la palabra
    while (n > 0) {
        getline(fin, line);
        int pos = 1;
        string r;
        stringstream ss(line);
        while (ss >> r) {
            for (int i = 0; i < r.size(); ++i) if (isalpha(r[i])) r[i] = tolower(r[i]);
            if (r == s) {
                --n;
                if (n == 0) {
                    cout << doc << "-" << linia << "-" << pos << endl;
                    break;
                }
            }
            ++pos;
        }
        ++linia;
    }
    
    fin.close();
}

//Primero el codigo compta.cc genera un archivo a partir de la entrada (detalles en el codigo)
//Despues prepara.cc genera un archivo a partir del anterior en el que indica en que posicion esta cada palabra en el anterior archivo
//Este codigo lee la entrada de la palabra de cada caso y calcula la respuesta
int main() {
    ifstream fin("/home/alex/codigos/tuenti/Challenge9/linias.txt");
    map<string, int> id;
    string str; int line;
    while (fin >> str >> line) id[str] = line;
    
    int casos;
    cin >> casos;
    for (int cas = 1; cas <= casos; ++cas) {
        string s;
        ll k;
        cin >> s >> k;
        for (int i = 0; i < s.size(); ++i) if (isalpha(s[i])) s[i] = tolower(s[i]);
        
        ifstream fin2("/home/alex/codigos/tuenti/Challenge9/bd.txt");
        fin2.seekg(id[s], ios::beg);
        getline(fin2, str);
        fin2.close();
        
        vector<ll> qtt;
        stringstream ss(str);
        ss >> str;
        ll x;
        while (ss >> x) qtt.push_back(x);
        while (qtt.size() < 800) qtt.push_back(qtt[qtt.size() - 1]);
        
        //Caso que no haya suficientes: No deberia pasar, no se dice que hacer
        if (qtt[799] < k) {
            cout << endl;
            continue;
        }
        
        //Hago una binaria para saber en que documento se encuentra
        int ini = 0, fin = 799;
        while (ini <= fin) {
            int m = (ini + fin)/2;
            if (qtt[m] >= k) fin = m - 1;
            else ini = m + 1;
        }
        if (fin + 1 == 0) busca(s, k, 1);
        else busca(s, k - qtt[fin], fin + 2);
    }
    fin.close();
}