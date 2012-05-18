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
#include <queue>

#define DBG(x, arg...)       //x, ##arg

using namespace std;

int main(int narg, char **arg)
{
    vector<long long> stack;
    string str;
    while(cin >> str)
    {
        if(str=="mirror") stack.back()=-stack.back(); // ok
        else if(str=="breadandfish") stack.push_back(stack.back()); // ok
        else if(str=="#") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(a*b);
        }
        else if(str=="fire") // (8267 8267 fire)=8267 ; (5 3 fire)=5 --> max?
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(max(a, b));
        }
        else if(str=="$") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(b-a);
        }
        else if(str=="dance") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(a);
            stack.push_back(b);
        }
        else if(str=="conquer") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(b%a);
        }
        else if(str=="&") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(b/a);
        }
        else if(str=="@") // ok
        {
            long long a=stack.back(); stack.pop_back();
            long long b=stack.back(); stack.pop_back();
            stack.push_back(a+b);
        }
        else if(str==".") // ok
        {
            cout << stack.back() << endl;
            stack.clear();
        }
        else stack.push_back(atoll(str.c_str()));
    }
    return 0;
}
