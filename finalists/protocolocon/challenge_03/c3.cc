//  -*- mode: c++; coding: utf-8; c-file-style: "stroustrup"; -*-

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits>
#include <set>
#include <stdio.h>

#define DBG(x, arg...)       //x, ##arg

using namespace std;

int main(int narg, char **arg)
{
    long long n, buy=0, buy_time=0, time=0, best=0, best_buy=0, best_sell=0;
    while(cin >> n)
    {
        if(!time) { buy=n; buy_time=0; }
        else if(n<buy) { buy=n; buy_time=time; }

        if(n-buy>best)
        {
            best=n-buy;
            best_buy=buy_time;
            best_sell=time;
        }
        time+=100;
    }

    cout << best_buy << " " << best_sell << " " << best << endl;

    return 0;
}
