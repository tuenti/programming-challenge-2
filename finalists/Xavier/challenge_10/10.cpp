#include <iostream>
#include <stack>
using namespace std;

int number(string& s) {
  int sum = 0;
  for (int i = 0; i < (signed)s.size(); ++i) {
    sum *= 10;
    sum += s[i] - '0';
  } 
  return sum;
}

int main() {
  stack<int> st;
  string s; 
  while (cin >> s) {
      if (s == ".") cout << st.top() << endl;
      else {
	if (s == "mirror") {
	  int t = st.top(); st.pop();
	  st.push(-t);
	} else if (s == "breadandfish") {
	  int t = st.top();
	  st.push(t);
	} else if (s == "fire") {
	  st.pop();
	} else if (s == "$") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(b - a);
	} else if (s == "&") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(b/a);	  
	} else if (s == "@") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(b + a);
	} else if (s == "dance") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(a);
	  st.push(b);
	} else if (s == "#") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(b * a);
	} else if (s == "conquer") {
	  int a = st.top(); st.pop(); 
	  int b = st.top(); st.pop();
	  st.push(b % a);
	} else st.push(number(s));
	
      }
  }
}