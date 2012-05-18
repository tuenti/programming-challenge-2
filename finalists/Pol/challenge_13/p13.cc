#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// What we have here is a permutation of the integers: 1..N
// We can separate this permutation into disjoint cycles of transitions.
// The least common multiple of the lengths of the cycles gives us
// the minimum number of times we need to apply the permutation to the sequence
// in order to get the original sequence, which is the answer to the problem.

// BigInt UPC: This ugly code is a library for handling big integers.
//<BIGINT>
typedef vector<int> VE;
typedef long long ll;
const ll base = 1000000000; // 9 zeros

class BI { public:
  VE v;    // el digit menys significatiu es v[0]
  int n;   // v.size()
  int sig; // 1: positiu o zero, -1: negatiu

  // GENERAL PER A TOT
  void zero() { v = VE(1, 0); n = sig = 1; }
  void remida(int i, int que=0) { v.resize(n = i, que); }

  void treuzeros(){
    while (--n and !v[n]);
    remida(n+1);
    if (n == 1 and !v[0]) sig = 1;
  }

  void parse(string num) {
    if (num[0] == '-') { sig = -1; num = num.substr(1); }
      else sig = 1;
    int m = num.size() - 1;
    v = VE(1 + m/9, 0); n = v.size();
    for (int i = m, exp = 0, pw = 1, pos = 0; i >= 0; --i, ++exp, pw *= 10) {
      if (exp == 9) { exp = 0; pw = 1; ++pos; }
      v[pos] += (num[i] - '0')*pw;
    }
    treuzeros();
  }

  // DESIGUALTATS
  // compara en valor absolut, 0: == b, positiu: > b; negatiu: < b
  inline int compabs(const BI &b) const {
    if (n != b.n) return n - b.n;
    for (int i = n - 1; i >= 0; --i)
      if (v[i] != b.v[i]) return v[i] - b.v[i];
    return 0;
  }

  // 0: == b, positiu: > b; negatiu: < b
  inline int compara(const BI &b) const {
    if (sig != b.sig) return sig - b.sig;
    return sig*compabs(b);
  }

  inline bool operator==(const BI &b) const { return !compara(b); }
  inline bool operator!=(const BI &b) const { return compara(b); }
  inline bool operator<(const BI &b)  const { return compara(b) < 0; }
  inline bool operator<=(const BI &b) const { return compara(b) <= 0; }
  inline bool operator>(const BI &b)  const { return compara(b) > 0; }
  inline bool operator>=(const BI &b) const { return compara(b) >= 0; }

  // |x| < 10^9
  inline bool operator==(int x) { return n == 1 and sig*v[0] == x; }

  // OPERACIONS EN VALOR ABSOLUT
  inline int dig(int i) { return (i < n ? v[i] : 0); }

  void suma(BI &b) {
    if (n < b.n) remida(b.n, 0);
    int ca = 0;
    for (int i = 0; i < n; ++i) {
      v[i] += b.dig(i) + ca; ca = v[i]/base; v[i] %= base;
    }
    if (ca) remida(n+1, ca);
  }

  // suposa >= b
  void resta(BI &b) {
    int ca = 0;
    for (int i = 0; i < n; ++i) {
      v[i] += base - b.dig(i) + ca; ca = v[i]/base - 1; v[i] %= base;
    }
    treuzeros();
  }

  // INICIALITZACIONS I COPIA
  BI() { zero(); }
  BI(const BI &b) { *this = b; }

  // |x| < 10^18
  BI(ll x) {
    sig = (x < 0 ? -1 : 1); x *= sig;
    if (x < base) { v = VE(1, x); n = 1; }
      else { v = VE(2); v[0] = x % base; v[1] = x/base; n = 2; }
  }

  BI(string num) { parse(num); }
  void operator=(const BI &b) { v = b.v; n = b.n; sig = b.sig; }

  // OPERACIONS
  void operator+=(BI &b) {
    if (sig == b.sig) return suma(b);
    if (compabs(b) >= 0) return resta(b);
    BI aux(b); aux.resta(*this); *this = aux;
  }

  void operator-=(BI &b) {
    if (&b == this) return zero();
    b.sig *= -1; operator+=(b); b.sig *= -1;
  }

  // |x| < 10^9
  void operator*=(int x) {
    if (x < 0) { sig *= -1; x *= -1; }
    remida(n + 1, 0);
    ll ca = 0;
    for (int i = 0; i < n; ++i) {
      ca += (ll)v[i]*x; v[i] = ca % base; ca /= base;
    }
    treuzeros();
  }

  void operator*=(BI &b) {
    BI c; c.remida(n + b.n, 0); c.sig = sig*b.sig;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < b.n; ++j) {
        int k = i + j;
        ll z = (ll)v[i]*b.v[j] + c.v[k], y;
        while ((y = z / base)) { c.v[k] = z % base; z = y + c.v[++k]; }
        c.v[k] = z;
      }
      c.treuzeros();
      *this = c;
  }

  // |x| < 10^9
  void operator/=(int x) {
    if (x < 0) { sig *= -1; x *= -1; }
    ll ca = 0;
    for (int i = n-1; i >= 0; --i ) {
      ca += v[i]; v[i] = ca/x; ca %= x; ca *= base;
    }
    treuzeros();
  }

  void operator/=(BI &b){
    if (compabs(b)<0) return zero();
    if (b.n==1) *this/=b.sig*b.v[0];
    else {
      int st = sig*b.sig, sb = b.sig; sig = b.sig = 1;
      vector<BI> VB,pot2;
      VB.push_back(b); pot2.push_back(1);
      BI curr=0;
      //primera pasada
      while (VB[VB.size()-1]<=*this){
        BI ultimo=VB[VB.size()-1];  ultimo+=ultimo; VB.push_back(ultimo);
        ultimo=pot2[pot2.size()-1]; ultimo+=ultimo; pot2.push_back(ultimo);
      }
      curr+=pot2[pot2.size()-2]; (*this)-=VB[VB.size()-2];
      //resto
      while ((*this)>=b){
        int i=0;
        while (VB[i]<=(*this)) i++;
        curr+=pot2[i-1]; (*this)-=VB[i-1];
      }
      (*this)=curr; sig = st; b.sig = sb;
    }
  }

  // |x| < 10^9; amb negatius funciona com C++
  ll mod(int x) {
    if (x < 0) x *= -1;
    ll ca = 0;
    for (int i = n-1; i >= 0; --i ) { ca *= base; ca += v[i]; ca %= x; }
    return ca;
  }

  void operator%=(BI &b) {
    BI r(*this); r /= b; r*= b; operator-=(r);
  }

  void mcdrec(BI &b, BI &c) {
    if (c == 0) return *this = b;
    b %= c; mcdrec(c, b);
  }

  void mcd(BI &b, BI& c) { BI bb(b), cc(c); mcdrec(bb, cc); }

// ENTRADA-SORTIDA
  friend ostream &operator<<(ostream &out, BI &b) {
    if (b.sig < 0) out << '-';
    int i = b.v.size() - 1;
    out << b.v[i];
    for (--i; i >= 0; --i) out << setw(9) << setfill('0') << b.v[i];
    return out;
  }

  friend istream &operator >>(istream &in, BI &b) {
    string num; in >> num; b.parse(num);
    return in;
  }
};
//</BIGINT>



// typedef long long ll;

// ll gcd(ll a, ll b) {
//   if (b == 0) return a;
//   return gcd(b, a%b);
// }

// ll lcm(ll a, ll b) {
//   return (a/gcd(a, b))*b;
// }

BI gcd(BI& a, BI& b) {
  if (b == 0) return a;
  BI m = a;
  m %= b;
  return gcd(b, m);
}

BI lcm(BI& a, BI& b) {
  BI g = gcd(a, b);
  BI res = a;
  res /= g;
  res *= b;
  return res;
}

int main() {
  int tcas;
  cin >> tcas;
  for (int cas = 1; cas <= tcas; ++cas) {
    int n, na;
    cin >> n >> na;
    int nb = n - na;
    
    vector<int> next(n);
    int a = na - 1, b = na + nb - 1, c = 0;
    while (0 <= a or na <= b) {
      if (0 <= a) next[a--] = c++;
      if (na <= b) next[b--] = c++;
    }
    
//     for (int i = 0; i < n; ++i) cerr << " " << next[i];
//     cerr << endl;
    
    BI res = 1;
    vector<bool> vist(n, false);
    for (int i = 0; i < n; ++i) {
      int s = 0, j = i;
      while (not vist[j]) {
        vist[j] = true;
        j = next[j];
        ++s;
      }
      if (s) {
        BI bigs = s;
        res = lcm(res, bigs);
      }
    }
    
    cout << "Case #" << cas << ": " << res << endl;
  }
}
