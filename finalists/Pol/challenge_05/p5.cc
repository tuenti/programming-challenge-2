#include <iostream>
using namespace std;

typedef long long ll;

// ****1****
// *       *
// 32      2
// *       *
// ****64***
// *       *
// 16      4
// *       *
// ****8****
const int leds[] = {
  1 + 2 + 4 + 8 + 16 + 32,      //0
  2 + 4,                        //1
  1 + 2 + 8 + 16 + 64,          //2
  1 + 2 + 4 + 8 + 64,           //3
  2 + 4 + 32 + 64,              //4
  1 + 4 + 8 + 32 + 64,          //5
  1 + 4 + 8 + 16 + 32 + 64,     //6
  1 + 2 + 4,                    //7
  1 + 2 + 4 + 8 + 16 + 32 + 64, //8
  1 + 2 + 4 + 8 + 32 + 64       //9
};
//                          jan feb mar apr may jun jul aug sep oct nov dec
const int daysmonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int onedaysum[24*60*60];



int leds_on_digit(int d) {
  int res = 0;
  for (int i = 0; i < 8; ++i)
    if ((leds[d]>>i)&1) ++res;
  return res;
}

int leds_new_digit(int a, int b) {
  int res = 0;
  for (int i = 0; i < 8; ++i)
    if (((leds[a]>>i)&1) == 0 and ((leds[b]>>i)&1) == 1) ++res;
  return res;
}

int leds_next_new(int t) {
  int h = t/(60*60);
  int m = (t/60)%60;
  int s = t%60;
  
  int t2 = (t + 1)%(24*60*60);
  int h2 = t2/(60*60);
  int m2 = (t2/60)%60;
  int s2 = t2%60;
  
  int res = 0;
  res += leds_new_digit(h/10, h2/10);
  res += leds_new_digit(h%10, h2%10);
  res += leds_new_digit(m/10, m2/10);
  res += leds_new_digit(m%10, m2%10);
  res += leds_new_digit(s/10, s2/10);
  res += leds_new_digit(s%10, s2%10);
  return res;
}

int leds_next_old(int t) {
  int t2 = (t + 1)%(24*60*60);
  int h2 = t2/(60*60);
  int m2 = (t2/60)%60;
  int s2 = t2%60;
  
  int res = 0;
  res += leds_on_digit(h2/10);
  res += leds_on_digit(h2%10);
  res += leds_on_digit(m2/10);
  res += leds_on_digit(m2%10);
  res += leds_on_digit(s2/10);
  res += leds_on_digit(s2%10);
  return res;
}

int leap_years(int year) {
  return year/4 - year/100 + year/400;
}

bool is_leap(int year) {
  if (year%400 == 0) return true;
  if (year%100 == 0) return false;
  return year%4 == 0;
}

ll fun(int year, int month, int day, int hour, int minute, int second) {
  ll res = (year - 1)*ll(365*24*60*60) + leap_years(year - 1)*ll(24*60*60);
  for (int m = 1; m < month; ++m) {
    res += daysmonth[m]*ll(24*60*60);
    if (m == 2 and is_leap(year)) res += 24*60*60;
  }
  res += (day - 1)*ll(24*60*60);
  res += hour*60*60 + minute*60 + second;
  return res;
}

void compute_onedaysum() {
  onedaysum[0] = leds_next_old(0) - leds_next_new(0);
  for (int i = 1; i < 24*60*60; ++i)
    onedaysum[i] = onedaysum[i - 1] + leds_next_old(i) - leds_next_new(i);
}

int sameday(int ta, int tb) {
  if (ta == tb) return 0;
  if (ta == 0) return onedaysum[tb - 1];
  return onedaysum[tb - 1] - onedaysum[ta - 1];
}

int main() {
  compute_onedaysum();
  
  char spam;
  int year1, month1, day1, hour1, minute1, second1;
  int year2, month2, day2, hour2, minute2, second2;
  while (cin >> year1 >> spam >> month1 >> spam >> day1
             >> hour1 >> spam >> minute1 >> spam >> second1
             >> spam
             >> year2 >> spam >> month2 >> spam >> day2
             >> hour2 >> spam >> minute2 >> spam >> second2) {
    ll t1 = fun(year1, month1, day1, hour1, minute1, second1);
    ll t2 = fun(year2, month2, day2, hour2, minute2, second2);
    
    if (t1/(24*60*60) == t2/(24*60*60)) {
      cout << sameday(t1%(24*60*60), t2%(24*60*60)) << endl;
    }
    else {
      ll res = sameday(t1%(24*60*60), 24*60*60);
      res += (t2/(24*60*60) - t1/(24*60*60) - 1)*ll(sameday(0, 24*60*60));
      res += sameday(0, t2%(24*60*60));
      cout << res << endl;
    }
  }
}
