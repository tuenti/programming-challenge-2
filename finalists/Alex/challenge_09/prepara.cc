#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> VS;
typedef long long ll;

string str(int x) {
    stringstream ss;
    ss << x;
    string s;
    ss >> s;
    return s;
}

//Crea un archivo indicando en que posicion del archivo generado por compta.cc esta cada palabra
int main() {
    string s;
    ll pos = 0;
    while (getline(cin, s)) {
        string r;
        stringstream ss(s);
        ss >> r;
        cout << r << " " << pos << endl;
        pos += s.size() + 1;
    }
}
