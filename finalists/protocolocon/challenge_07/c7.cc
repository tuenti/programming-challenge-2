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

struct Letter
{
    set<char> prev, next;
} letter[128];

map<unsigned long long, vector<string> > sol;
unsigned long long masks[128];
int n_masks;

void prev(Letter &let, set<char> &s)
{
    for(set<char>::iterator it=let.prev.begin(); it!=let.prev.end(); ++it)
    {
        if(s.find(*it)!=s.end()) continue;
        s.insert(*it);
        prev(letter[int(*it)], s);
    }
}

void next(Letter &let, set<char> &s)
{
    for(set<char>::iterator it=let.next.begin(); it!=let.next.end(); ++it)
    {
        if(s.find(*it)!=s.end()) continue;
        s.insert(*it);
        next(letter[int(*it)], s);
    }
}

unsigned long long index(char c)
{
    return 1LL << (c<='9' ? (c-'0') : (c<='Z' ? c-'A'+10 : c-'a'+36 ));
}

void construct(string &str, int i, unsigned long long mask, unsigned long long mask_final)
{
    if(mask==mask_final)
    {
        DBG(printf("construct: %s %d %lld\n", str.c_str(), i, mask));
        sol[mask_final].push_back(str);
        return;
    }
    if(index(i) & mask) return;
    mask|=index(i);

    int next_i=0, best_next=-1000;
    for(int j=0; j<128; j++)
    {
        if(!isalnum(j)) continue;
        unsigned long long idx=index(j);
        if((mask_final & idx) && !(mask & idx))
        {
            set<char> s_prev, s_next;
            prev(letter[j], s_prev);
            next(letter[j], s_next);
            int now=s_next.size()-s_prev.size();
            if(now>best_next)
            {
                best_next=now;
                next_i=j;
            }
        }
    }

    int ini=0, fin=str.size();

    for(unsigned j=0; j<str.size(); j++)
    {
        Letter &let=letter[int(str[j])];
        for(set<char>::iterator it=let.prev.begin(); it!=let.prev.end(); ++it) if(*it==i) fin=j;
        for(set<char>::iterator it=let.next.begin(); it!=let.next.end(); ++it) if(*it==i) ini=j+1;
    }
    for(int j=ini; j<=fin; j++)
    {
        string str2=str;
        str2.insert(j, 1, i);
        construct(str2, next_i, mask, mask_final);
    }
}

void compose_merge(string &str, string &a, int ia, string &b, int ib, vector<string> &add)
{
    if(ia<int(a.size())) { str+=a[ia]; compose_merge(str, a, ia+1, b, ib, add); str.resize(str.size()-1); }
    if(ib<int(b.size())) { str+=b[ib]; compose_merge(str, a, ia, b, ib+1, add); str.resize(str.size()-1); }
    if(ia==int(a.size()) && ib==int(b.size())) add.push_back(str);
}

void compose_merge(vector<string> &comp, string &str)
{
    vector<string> add;
    string str_;
    for(unsigned i=0; i<comp.size(); i++) compose_merge(str_, comp[i], 0, str, 0, add);
    comp.swap(add);
}

int main(int narg, char **arg)
{
    string str;
    set<char> all_seen;
    while(cin >> str)
    {
        for(unsigned i=0; i<str.size(); i++)
        {
            all_seen.insert(str[i]);
            Letter &let=letter[int(str[i])];
            if(i) let.prev.insert(str[i-1]);
            if(i<str.size()-1) let.next.insert(str[i+1]);
        }
    }

    for(int i=0; i<128; i++)
    {
        Letter &let=letter[i];
        if(let.prev.empty() && let.next.empty()) continue;
        set<char> s_prev, s_next;
        for(set<char>::iterator it=let.prev.begin(); it!=let.prev.end(); ++it) prev(letter[int(*it)], s_prev);
        for(set<char>::iterator it=s_prev.begin(); it!=s_prev.end(); ++it) let.prev.erase(*it);
        for(set<char>::iterator it=let.next.begin(); it!=let.next.end(); ++it) next(letter[int(*it)], s_next);
        for(set<char>::iterator it=s_next.begin(); it!=s_next.end(); ++it) let.next.erase(*it);
    }

    DBG(
        for(int i=0; i<128; i++)
        {
            Letter &let=letter[i];
            for(set<char>::iterator it=let.prev.begin(); it!=let.prev.end(); ++it) printf("PREV %c -> %c\n", *it, i);
            for(set<char>::iterator it=let.next.begin(); it!=let.next.end(); ++it) printf("NEXT %c -> %c\n", i, *it);
        }
    );

    // masks
    unsigned long long all_mask=0;
    for(int i=0; i<128; i++)
    {
        if(!isalnum(i) || (all_mask & index(i))) continue;
        Letter &let=letter[i];
        if(let.prev.empty() && let.next.empty()) continue;
        set<char> s;
        s.insert(i);
        int last=0;
        while(last!=int(s.size()))
        {
            last=s.size();
            for(set<char>::iterator it=s.begin(); it!=s.end(); ++it) { prev(letter[int(*it)], s); next(letter[int(*it)], s); }
        }

        unsigned long long m=0;
        for(set<char>::iterator it=s.begin(); it!=s.end(); ++it) m|=index(*it);
        all_mask|=m;
        masks[n_masks++]=m;

        DBG(printf("%d %016llx\n", n_masks, m));
    }

    // construct
    for(int i=0; i<n_masks; i++)
    {
        unsigned long long m=masks[i];
        for(int j=0; j<128; j++)
        {
            if(!isalnum(j)) continue;
            if(m & index(j))
            {
                string str;
                construct(str, j, 0, m);
                break;
            }
        }
    }

    vector<string> solution;

    bool end=false;
    vector<int> iter_mask(n_masks);
    while(!end)
    {
        vector<string> compose(1, sol[masks[0]][iter_mask[0]]);
        for(int i=1; i<n_masks; i++) compose_merge(compose, sol[masks[i]][iter_mask[i]]);

        DBG(for(int i=0; i<n_masks; i++) printf("%016llx %d %s | ", masks[i], iter_mask[i], sol[masks[i]][iter_mask[i]].c_str()); printf("\n"));
        DBG(for(unsigned i=0; i<compose.size(); i++) printf("%s\n", compose[i].c_str()));

        solution.insert(solution.end(), compose.begin(), compose.end());

        int i=0;
        while(true)
        {
            if(i==n_masks) { end=true; break; }

            iter_mask[i]++;
            if(iter_mask[i]>=int(sol[masks[i]].size()))
            {
                iter_mask[i]=0;
                i++;
            }
            else break;
        }
    }

    sort(solution.begin(), solution.end());
    for(unsigned i=0; i<solution.size(); i++) cout << solution[i] << endl;
}
