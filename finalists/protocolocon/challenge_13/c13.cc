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
    int t;
    cin >> t;
    for(int it=0; it<t; it++)
    {
        int n, l;
        cin >> n >> l;

        int ll=min(l, n-l);

        vector<int> p(n);
        for(int i=0; i<ll; i++)
        {
            p[(i<<1)  ]=l-i-1;
            p[(i<<1)+1]=n-i-1;
        }
        if(ll==l) for(int i=0; i<n-(ll<<1); i++) p[(ll<<1)+i]=n-ll-i-1;
        else      for(int i=0; i<n-(ll<<1); i++) p[(ll<<1)+i]=n-(ll<<1)-i-1;

        vector<int> q(n);
        for(int i=0; i<n; i++) q[p[i]]=i;

        DBG(for(int i=0; i<n; i++) printf("%d ", q[i]); printf("\n"));

        vector<bool> seen(n);
        set<unsigned long long> factors;
        for(int i=0; i<n; i++)
        {
            int counter=0, m=i;
            if(seen[m]) continue;
            do { m=q[m]; counter++; seen[m]=true; } while(m!=i);
            factors.insert(counter);
        }
        unsigned long long result=1;
        for(set<unsigned long long>::iterator i=factors.begin(); i!=factors.end(); ++i)
        {
            unsigned long long f=*i;
            unsigned long long g=__gcd(result, f);
            result*=f/g;
            DBG(printf("%lld %lld\n", f, f/g));
        }

        cout << "Case #" << (it+1) << ": " << result << endl;
    }

    return 0;
}
