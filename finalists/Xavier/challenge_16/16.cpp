#include <iostream>
#include <cmath>
using namespace std;

double dist(double v[], double v2[], int n) {
  double sum = 0;
  for (int i = 0; i < n; ++i) sum += (v[i] - v2[i])*(v[i] - v2[i]);
  return sqrt(sum);
}

int distD(int v[], int v2[], int n) {
  double sum = 0;
  for (int i = 0; i < n; ++i) sum += fabs(v[i] - v2[i]);
  return sum;
}

void norm(double v[], int n) {
  double sum = 0;
  for (int i = 0; i < n; ++i) sum += v[i]*v[i];
  for (int i = 0; i < n; ++i) v[i] /= sqrt(sum);
}

int main() {
  int r, u, s;
  cin >> s >> u >> r;
  double programas[s][r];
  int bueno[s];
  for (int i = 0; i < s; ++i) {
    char c; cin >> c;
    bueno[i] = (c == 'S')?1:0;
    for (int j = 0; j < r; ++j) 
      cin >> programas[i][j];
    norm(programas[i],r);
  }
  
  int llamadasMalas = 0;
  for (int i = 0; i < u; ++i) {
    double unknown[r];
    int llamadas = 0;
    for (int j = 0; j < r; ++j) {
      cin >> unknown[j];
      llamadas += unknown[j];
    }
    norm(unknown,r);
    double var = 0;
    for (int j = 0; j < s; ++j) 
      if (bueno[j]) var += 1/dist(unknown, programas[j], r);
      else var -= 1/dist(unknown, programas[j], r);
  
    if (var < 0) llamadasMalas += llamadas;
    
  }
  cout << llamadasMalas << endl;
}