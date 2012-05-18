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
#include <cassert>

#define DBG(x, arg...)       //x, ##arg

using namespace std;

int main(int narg, char **arg)
{
    int t;
    cin >> t;
    vector<int> groups;
    for(int it=0; it<t; it++)
    {
        long long n_race, n_kart, n_group;
        cin >> n_race >> n_kart >> n_group;
        groups.resize(n_group);
        for(int i=0; i<n_group; i++) cin >> groups[i];

        vector<pair<long long, long long> > one_pass(n_group, make_pair(-1, -1)); // races, litres

        long long litres=0, i_group=0;
        for(long long i=0; i<n_race; i++)
        {
            if(one_pass[i_group].first>=0)
            {
                // known
                long long r=(n_race-i)/(i-one_pass[i_group].first);
                litres+=r*(litres-one_pass[i_group].second);
                i+=r*(i-one_pass[i_group].first);
                if(i>=n_race) break;
            }
            one_pass[i_group]=make_pair(i, litres);

            long long i_kart=0, first_group=i_group;
            while(i_kart+groups[i_group]<=n_kart)
            {
                i_kart+=groups[i_group];
                i_group++;
                if(i_group==int(groups.size())) i_group=0;
                if(i_group==first_group) break;
            }
            assert(i_kart);
            litres+=i_kart;
        }
        cout << litres << endl;
    }
}
