#include <iostream>
using namespace std;

int MAYUS_KEY = 10;

bool mayuscula(char a) {
  return 'A' <= a and a <= 'Z';
}

bool minuscula(char a) {
  return 'a' <= a and a <= 'z';
}

int KEY[] = {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,6,7,7,7,8,8,8,8};

int key(char a) {
  if (mayuscula(a)) a = a - 'A' + 'a';
  if (a == ' ') return 0;
  if ('1' <= a and a <= '9') return a - '1';
  if (a == '0') return 9;
  return KEY[a - 'a'];
}

int TYPE[]= {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};
int numTYPE[] = {1,2,4,4,4,4,4,5,4,5};

int type(char a) {
  if (mayuscula(a)) a = a - 'A' + 'a';
  if ('a' <= a and a <= 'z') return TYPE[a - 'a']*100;
  if ('0' <= a and a <= '9') return numTYPE[a - '0']*100;
  return 100;
}

//calculated using program
int GOTO[11][11] = {
{500,200,400,300,350,550,600,650,700,950,1000}
,{200,500,200,350,300,350,650,600,650,900,950}
,{400,200,500,550,350,300,700,650,600,950,900}
,{300,350,550,500,200,400,300,350,550,650,700}
,{350,300,350,200,500,200,350,300,350,600,650}
,{550,350,300,400,200,500,550,350,300,650,600}
,{600,650,700,300,350,550,500,200,400,350,550}
,{650,600,650,350,300,350,200,500,200,300,350}
,{700,650,600,550,350,300,400,200,500,350,300}
,{950,900,950,650,600,650,350,300,350,500,200}
,{1000,950,900,700,650,600,550,350,300,200,500}};
int goTo(int key, int next_key) {
  return GOTO[key][next_key];
}

int main() {
  int n; cin >> n;
  string s;
  getline(cin,s);
  while (n--) {
    getline(cin,s); 
    long long sum = 0; 
    int act_key = 9;
    bool mayus = false;
    
    for (int i = 0; i < s.size(); ++i) {
      if (mayuscula(s[i]) and !mayus) {
	  //cerr << "i go to mayus" << endl;
	  sum += goTo(act_key,  MAYUS_KEY);
	  act_key = MAYUS_KEY;
	  sum += 100;
	  mayus = true;	
	  cerr << sum << endl;
      } else if (minuscula(s[i]) and mayus) {
	  sum += goTo(act_key, MAYUS_KEY);
	  act_key = MAYUS_KEY;
	  sum += 100;
	  mayus = false;
      }
      int next_key = key(s[i]);
     //cerr << "i am " << act_key << " go to " << next_key << " " << s[i] << endl;
      sum += goTo(act_key, next_key);
      act_key = next_key;
      sum += type(s[i]);
      //cerr << sum << endl;
    }
    cout << sum << endl;  
  }
}