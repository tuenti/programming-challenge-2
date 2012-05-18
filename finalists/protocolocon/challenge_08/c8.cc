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
    string clones, trans;
    cin >> clones;

    vector<string> complete_tr(128);
    for(int i='0'; i<='z'; i++)
    {
        char c[2]={i, 0};
        complete_tr[i]=string(c);
    }

    while(cin >> trans)
    {
        vector<string> tr(128);
        for(int i='0'; i<='z'; i++)
        {
            char c[2]={i, 0};
            tr[i]=string(c);
        }

        for(unsigned i=0; i<trans.size(); )
        {
            int c=trans[i];
            i+=3;
            int comma=trans.find(',', i);
            tr[c]=trans.substr(i, comma-i);
            if(size_t(comma)==string::npos) break;
            i=comma+1;
        }

        for(int i='0'; i<='z'; i++)
        {
            string new_str;
            for(unsigned j=0; j<complete_tr[i].size(); j++)
            {
                new_str+=tr[complete_tr[i][j]];
            }
            complete_tr[i]=new_str;
        }
    }

    for(unsigned i=0; i<clones.size(); i++) cout << complete_tr[clones[i]];

    DBG(for(int i='0'; i<='z'; i++) printf("%c {%s}\n\n", i, complete_tr[i].c_str()));
    return 0;
}
