#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;
/*
    1 point: A E I L N O R S T U
    2 points: D G
    3 points: B C M P
    4 points: F H V W Y
    5 points: K
    8 points: J X
    10 points: Q Z
    */

	//  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z 
int P[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,1, 1, 1, 1, 4, 4, 8, 4, 10};

int pointsWord(const string& s) {
  int sum = 0;
  for (int i = 0; i < (signed)s.size(); ++i)
    sum += P[s[i] - 'A'];
  return sum;
}
  
bool can(const string& word, const string& letter, const string& tauler) {
    
    bool totalInside = false;
    vector<bool> lletraMaUsada(letter.size(), false);
    vector<bool> lletraParaulaTrobada(word.size(), false);
    vector<bool> lletraParaulaDintreTauler(word.size(), false);
    int lletresParaulaTrobades = 0;
    for (int i = 0; i < (signed)word.size(); ++i) {
      for(int j = 0; j < (signed)letter.size(); ++j)
	if (letter[j] == word[i] and !lletraMaUsada[j]) {
	  lletraMaUsada[j] = true; 
	  lletraParaulaTrobada[i] = true;
	  ++lletresParaulaTrobades;
	  break;
	}
      for (int j = 0; j < (signed)tauler.size(); ++j) 
	if (tauler[j] == word[i]) {totalInside = true; lletraParaulaDintreTauler[i] = true;}
    }
// 	if (word == "ZING") {
// 	    for (int i = 0; i < (signed) word.size(); ++i) cout << lletraParaulaDintreTauler[i] << " "; cout << endl;
// 	    for (int i = 0; i < (signed)letter.size(); ++i) cout << lletraMaUsada[i] << " "; cout << endl;
// 	    for (int i = 0; i < (signed) word.size(); ++i) cout << lletraParaulaTrobada[i] << " "; cout << endl;
// 	    cout << lletresParaulaTrobades << endl;
// 	}
	
	
    if (lletresParaulaTrobades == (signed)word.size() and totalInside) return true;
    if (lletresParaulaTrobades == (signed)word.size() -1) 
      for (int i = 0; i < (signed)word.size(); ++i) 
	if (!lletraParaulaTrobada[i] and lletraParaulaDintreTauler[i]) return true;
    return false;   
}

int main() {
    fstream fin("words.txt", fstream::in);
    vector<string> v;
    vector<int> points;
    string aux;
    while (fin >> aux) {
      v.push_back(aux);
      points.push_back(pointsWord(aux));      
    }
    int n; cin >> n;
    string a, b;
    while (cin >> a >> b) {
      int maxpoints = 0;
      int maxstring = 0;
      for (int i = 0; i < (signed)v.size(); ++i) {
	  if (can(v[i],a,b) and points[i] > maxpoints) {
	    maxpoints = points[i];
	    maxstring = i;
	  }	    
       }
       if (maxpoints == 0) cout << endl;
       else cout << v[maxstring] << " " << maxpoints << endl;
    }
}