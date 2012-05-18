#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int INF  = 1000000000;
ll M[11][11];

//Inicializo los vectores de las teclas (para saber en que tecla esta cada caracter y cuanto se pulsa)
//Hago un Floyd-Warshall para calcular el minimo tiempo entre pares de teclas
void init() {
    
    
    for (int i = 0; i < 11; ++i) for (int j = 0; j < 11; ++j) M[i][j] = INF;
    for (int i = 0; i < 11; ++i) M[i][i] = 0;
    //1 2 3
    //4 5 6
    //7 8 9
    //  0 10
    M[0][8] = M[8][0] = 300;
    M[0][7] = M[7][0] = M[0][9] = M[9][0] = 350;
    M[0][10] = M[10][0] = 200;
    M[1][2] = M[2][1] = 200;
    M[1][4] = M[4][1] = 300;
    M[1][5] = M[5][1] = 350;
    M[2][3] = M[3][2] = 200;
    M[2][5] = M[5][2] = 300;
    M[2][4] = M[4][2] = M[2][6] = M[6][2] = 350;
    M[3][6] = M[6][3] = 300;
    M[3][5] = M[5][3] = 350;
    M[4][5] = M[5][4] = 200;
    M[4][7] = M[7][4] = 300;
    M[4][8] = M[8][4] = 350;
    M[5][6] = M[6][5] = 200;
    M[5][8] = M[8][5] = 300;
    M[5][7] = M[7][5] = M[5][9] = M[9][5] = 350;
    M[6][9] = M[9][6] = 300;
    M[6][8] = M[8][6] = 350;
    M[7][8] = M[8][7] = 200;
    M[8][9] = M[9][8] = 200;
    M[8][10] = M[10][8] = 350;
    M[9][10] = M[10][9] = 300;
    
    //Floyd-Warshall
    for (int k = 0; k < 11; ++k) 
        for (int i = 0; i < 11; ++i) 
            for (int j = 0; j < 11; ++j) 
                M[i][j] = min(M[i][j], M[i][k] + M[k][j]);
}

int is_mayus(char c) {
    if ('A' <= c and c <= 'Z') return 1;
    return 0;
}

int tecla(char c) {
    if (c == ' ') return 1;
    if (isdigit(c)) return c - '0';
    c = toupper(c);
    if (c >= 'A' and c <= 'C') return 2;
    if (c >= 'D' and c <= 'F') return 3;
    if (c >= 'G' and c <= 'I') return 4;
    if (c >= 'J' and c <= 'L') return 5;
    if (c >= 'M' and c <= 'O') return 6;
    if (c >= 'P' and c <= 'S') return 7;
    if (c >= 'T' and c <= 'V') return 8;
    return 9;
}

int veces(char c) {
    if (c == ' ') return 1;
    if (isdigit(c)) {
        if (c == '0') return 1;
        if (c == '1') return 2;
        if (c == '7' or c == '9') return 5;
        return 4;
    }
    c = toupper(c);
    if (c >= 'A' and c <= 'C') return c - 'A' + 1;
    if (c >= 'D' and c <= 'F') return c - 'D' + 1;
    if (c >= 'G' and c <= 'I') return c - 'G' + 1;
    if (c >= 'J' and c <= 'L') return c - 'J' + 1;
    if (c >= 'M' and c <= 'O') return c - 'M' + 1;
    if (c >= 'P' and c <= 'S') return c - 'P' + 1;
    if (c >= 'T' and c <= 'V') return c - 'T' + 1;
    return c - 'W' + 1;
}

void solve(string& s) {
    int mayus = 0, pos = 0;
    ll time = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (isalpha(s[i]) and mayus != is_mayus(s[i])) {
            time += ll(M[pos][10] + 100);
            pos = 10;
            mayus = 1 - mayus;
            --i;
        }
        else {
            if (tecla(s[i]) == pos and i > 0) time += 500LL;
            time += ll(M[pos][tecla(s[i])] + 100*veces(s[i]));
            pos = tecla(s[i]);
        }
    }
    cout << time << endl;
}

int main() {
    init();
    
    //Lectura de la entrada
    int casos;
    cin >> casos;
    cin.ignore();
    for (int cas = 1; cas <= casos; ++cas) {
        string s;
        getline(cin, s);
        solve(s);
    }
}