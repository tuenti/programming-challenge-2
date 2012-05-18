#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

#define X first
#define Y second

typedef pair<int, int> P;

const int TVER = 300;
const int THOR = 200;
const int TDIAG = 350;
const int TPRESS = 100;
const int TSAME = 500;

// 1 2 3
// 4 5 6
// 7 8 9
//   0 ^

const P position[] = {
  P(3, 1), //0
  P(0, 0), //1
  P(0, 1), //2
  P(0, 2), //3
  P(1, 0), //4
  P(1, 1), //5
  P(1, 2), //6
  P(2, 0), //7
  P(2, 1), //8
  P(2, 2), //9
  P(3, 2), //10~^
};
//                        a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
const int abcbutton[] = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9 };
const int abctimes[] =  { 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4 };
//                       0  1  2  3  4  5  6  7  8  9
const int numtimes[] = { 1, 2, 4, 4, 4, 4, 4, 5, 4, 5 };

inline int dist(int a, int b) {
  int r = abs(position[a].X - position[b].X);
  int c = abs(position[a].Y - position[b].Y);
  int m = min(r, c);
  return TDIAG*m + TVER*(r - m) + THOR*(c - m);
}

int main() {
  int tcas;
  cin >> tcas;
  
  string line;
  getline(cin, line);
  
  for (int cas = 1; cas <= tcas; ++cas) {
    getline(cin, line);
    int n = line.size();
    
    int pos = 0;  // finger's position
    int caps = 0; // caps lock on?
    
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if ('a' <= line[i] and line[i] <= 'z') {      // lowercase
        if (caps == 1) {
          res += dist(pos, 10) + TPRESS;
          pos = 10;
          caps = 0;
        }
        int b = abcbutton[line[i] - 'a'];
        int t = abctimes[line[i] - 'a'];
        if (pos == b) res += TSAME;
        res += dist(pos, b) + t*TPRESS;
        pos = b;
      }
      else if ('A' <= line[i] and line[i] <= 'Z') { // uppercase
        if (caps == 0) {
          res += dist(pos, 10) + TPRESS;
          pos = 10;
          caps = 1;
        }
        int b = abcbutton[line[i] - 'A'];
        int t = abctimes[line[i] - 'A'];
        if (pos == b) res += TSAME;
        res += dist(pos, b) + t*TPRESS;
        pos = b;
      }
      else if ('0' <= line[i] and line[i] <= '9') { // digit
        int b = line[i] - '0';
        int t = numtimes[b];
        if (i > 0 and pos == b) res += TSAME; // one has to wait if wants to type two consecutive zeros
        res += dist(pos, b) + t*TPRESS;
        pos = b;
      }
      else {                                        // space
        if (pos == 1) res += TSAME;
        res += dist(pos, 1) + TPRESS;
        pos = 1;
      }
    }
    
    cout << res << endl;
  }
}
