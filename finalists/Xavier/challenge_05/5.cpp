#include <iostream>
#include <sstream>
using namespace std;

typedef long long ll;

inline ll pes(ll y, ll m, ll d) {
   m = (m + 9)%12;  y = y - m/10;
   return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);
}

inline ll days(int y1, int m1, int d1, int y2, int m2, int d2) {
   return pes(y2, m2, d2) - pes(y1,m1,d1);
}

int L1[] = {6,2,5,5,4,5,6,3,7,6};

int L2[10][10] = {
 //0 1 2 3 4 5 6 7 8 9 
  {0,0,0,0,0,0,0,0,0,0},  //0
  {0,0,4,0,0,0,0,0,0,0},  //1
  {2,0,0,1,0,0,0,0,0,0},  //2
  {2,0,0,0,1,0,0,0,0,0},  //3
  {0,0,0,0,0,2,0,0,0,0},  //4
  {2,0,0,0,0,0,1,0,0,0},  //5
  {0,0,0,0,0,0,0,1,0,0},  //6
  {0,0,0,0,0,0,0,0,4,0},  //7
  {0,0,0,0,0,0,0,0,0,0},  //8
  {1,0,0,0,0,0,0,0,0,0}   //9
}; 

int l1(int h1, int m1, int s1, int h2, int m2, int s2) {
  return L1[h2%10] + L1[h2/10] + L1[m2%10] + L1[m2/10] + L1[s2%10] + L1[s2/10];  
}

int l2(int h1, int m1, int s1, int h2, int m2, int s2) {
  return L2[h1/10][h2/10] + L2[h1%10][h2%10] +
	 L2[m1/10][m2/10] + L2[m1%10][m2%10] + 
	 L2[s1/10][s2/10] + L2[s1%10][s2%10];
}

ll cost(int h1, int m1, int s1, int h2, int m2, int s2, int (*lights)(int,int,int,int,int,int)) {
  //cerr << "H " << h1 << " " << m1 << " " << s1 << " " << h2 << " " << m2 << " " << s2 << endl;
  ll sum = 0;
  bool getin = false;
  if (h2 == -1) {h2 = 0; getin = true;}
  while ((h1 != h2 or m1 != m2 or s1 != s2) or (h1 == h2 and m1 == m2 and s1 == s2 and getin)) {
    getin = false;
    int ah = h1, am = m1, as = s1;
    ++as; 
    if (as == 60) {
      as = 0; ++am;
      if (am == 60) {
	am = 0; ++ah;
	if (ah == 24) ah = 0;
      }
    }
    sum += lights(h1,m1,s1,ah,am,as);
    h1 = ah; m1 = am; s1 = as;    
    //cerr << "lets simulate 2 " << h1 << " " << m1 << " " << s1 << endl;
  
  }
  return sum;
}

int main() {
  string s;
  ll cd1 = cost(0,0,0,-1,0,0,l1), cd2 = cost(0,0,0,-1,0,0,l2);
  
  while (getline(cin,s)) {
    stringstream lin(s);
    char c;
    
    int y1,mth1,d1,h1,m1,s1;
    int y2,mth2,d2,h2,m2,s2;
    lin >> y1 >> c >> mth1 >> c >> d1 >> h1 >> c >> m1>> c >> s1 >> c;
    lin >> y2 >> c >> mth2 >> c >> d2 >> h2 >> c >> m2>> c >> s2;
    
    int daysb = days(y1,mth1,d1,y2,mth2,d2);
    cout << cost(h1,m1,s1,-1,0,0,l1) + cost(0,0,0,h2,m2,s2,l1) + (daysb - 1)*cd1
          - cost(h1,m1,s1,-1,0,0,l2) - cost(0,0,0,h2,m2,s2,l2) - (daysb - 1)*cd2  << endl;
  }  
}