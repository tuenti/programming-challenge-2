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

int count_ones(unsigned long long x)
{
    int counter=0;
    while(x)
    {
        if(x&1) counter++;
        x>>=1;
    }
    return counter;
}

int bits(unsigned long long x)
{
    int counter=0;
    while(x)
    {
        counter++;
        x>>=1;
    }
    return counter;
}

int main(int narg, char **arg)
{
    int t;
    cin >> t;
    for(int it=0; it<t; it++)
    {
        unsigned long long n;
        cin >> n;

        int number=bits(n)-1+count_ones(n- (0xffffffffffffffffLL >> (64-bits(n)+1)));

        cout << "Case #" << (it+1) << ": " << number << endl;
    }
    return 0;
}
