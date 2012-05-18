#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef vector<long long> vi;

long long kadane(const vi& v, int &i, int &j) {
  long long maxSum = 0; int maxStart = -1, maxEnd = -1;
  long long  currentSum = 0; int currentStart = 0;
  for (int currentEnd = 0; currentEnd < v.size(); ++currentEnd) {
    currentSum += v[currentEnd];
    if (currentSum > maxSum) {
      maxStart = currentStart; maxEnd = currentEnd; maxSum = currentSum;
    }
    if (currentSum < 0) {
      currentStart = currentEnd +1;
      currentSum = 0;
    }
  }
  i = maxStart; j = maxEnd;
  return maxSum;
}

int main() {
  vi v;
  long long a, b, c;
  scanf("%lld %lld", &a, &b);
  v.push_back(b - a);
  while (scanf("%lld", &c) != EOF) {
    a = b;
    b = c;
    v.push_back(b - a);
  }
  int i, j;
  long long benefit = kadane(v,i,j);
  if (i == -1) {
    cout << "Hi" << endl;
    benefit = v[0]; i = 0; j = 0;
    for (int k = 0; k < v.size(); ++k) {
	if (v[k] > benefit) {
	    j =  i = k;
	    benefit = v[k];	  
	}
    }
  }
  cout << i*100 << " " << (j+1)*100 << " " << benefit << endl;
}