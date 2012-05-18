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

bool check(long long width, long long height, const char *str, long long font_size)
{
    if(font_size>height) return false;
    int pos[2]={0, 0};
    for(int i=0, last=0; ; i++)
    {
        if(!str[i] || str[i]==' ')
        {
            int n_char=i-last;
            long long word_width=n_char*font_size;
            if(word_width>width) return false;
            if(pos[1]) pos[1]+=font_size; // space
            if(pos[1]+word_width>width)
            {
                // new line
                pos[1]=word_width;
                pos[0]+=font_size;
                if(pos[0]+font_size>height) return false;
            }
            else
            {
                // continue
                pos[1]+=word_width;
            }
            last=i+1;
            if(!str[i]) break;
        }
    }
    return true;
}

int main(int narg, char **arg)
{
    int t;
    cin >> t;

    size_t max_str=0;
    char *str=NULL;

    for(int it=0; it<t; it++)
    {
        long long W, H, ct;
        cin >> W >> H >> ct;

        // read string
        getline(&str, &max_str, stdin);
        int n_str=getline(&str, &max_str, stdin);
        if(str[n_str-1]=='\n') str[--n_str]=0;
        while(n_str>1 && str[n_str-1]==' ') str[--n_str]=0;

        long long width=W*ct, height=H*ct, minim=1, maxim=max(width, height);
        while(minim<maxim)
        {
            long long middle=(minim+maxim)>>1;
            if(check(width, height, str, middle)) minim=middle+1; else maxim=middle;
        }
        if(!check(width, height, str, minim)) minim--;

        int n_letter=0;
        for(int i=0; str[i]; i++) if(str[i]!=' ') n_letter++;

        cout << "Case #" << (it+1) << ": " << (long long)(ceil(n_letter*double(minim*minim)*0.5/double(ct))) << endl;
    }
    return 0;
}
