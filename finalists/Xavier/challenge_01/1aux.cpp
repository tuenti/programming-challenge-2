#include <vector>
#include <queue>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

const int oo = 1000000000;

// HE USADO ESTO PARA CALCULAR LA MATRIZ DE DISTANCIAS

int main() {
  vvi dist(11, vi(11,oo));
  for (int i = 0; i < 11; ++i) 
    dist[i][i] = 0;
  
  //0 1 2
  //3 4 5
  //6 7 8
  //- 9 10
    
  //down/up 300, right/left: 200, diagonal 350
  
  dist[0][1] = 200; dist[0][3] = 300; dist[0][4] = 350;
  dist[1][2] = 200; dist[1][3] = 350; dist[1][4] = 300; dist[1][5] = 350;
  dist[2][4] = 350; dist[2][5] = 300;
  dist[3][4] = 200; dist[3][6] = 300; dist[3][7] = 350;
  dist[4][6] = 350; dist[4][7] = 300; dist[4][8] = 350; dist[4][5] = 200; 
  dist[5][7] = 350; dist[5][8] = 300;
  dist[6][9] = 350; dist[6][7] = 200;
  dist[7][8] = 200; dist[7][9] = 300; dist[7][10] = 350; 
  dist[8][9] = 350; dist[8][10] = 300;
  dist[9][10] = 200;
  for (int i = 0; i < 11; ++i)
    for (int j = 0; j < 11; ++j)
      dist[i][j] = dist[j][i] = min(dist[i][j], dist[j][i]);
  
  
  for (int k = 0; k < 11; ++k)
    for (int i = 0; i < 11; ++i)
      for (int j = 0; j < 11; ++j)
	dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      
  for (int i = 0; i < 11; ++i) {
    if (i != 0) cout << ",";
    cout <<  "{";
    for (int j = 0; j < 11; ++j) {
      if (j != 0) cout << ",";
      cout << dist[i][j];
    }
    cout << "}" << endl;
  }
}
      