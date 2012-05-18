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

int reverse(int i, int n_bits)
{
    int j=0;
    for(int k=0; k<n_bits; k++)
    {
        j<<=1;
        j|=i&1;
        i>>=1;
    }
    return j;
}

void print_binary(int n, int n_bits)
{
    for(int i=0; i<n_bits; i++)
    {
        n<<=1;
        printf("%c", '0'+((n>>n_bits)&1));
    }
}

int hamming(int n, int n_bits, int n_bits_code)
{
    DBG(print_binary(n, n_bits); printf(" "));

    // extend n
    int n_coded=0;
    for(int i=1; i<=n_bits_code; i++)
    {
        n_coded<<=1;
        if(i & (i-1)) { n<<=1; n_coded|=(n>>n_bits)&1; }
    }

    // calculate parity bits
    for(int i=1; i<=n_bits_code; i++)
    {
        if(i & (i-1)) continue;
        int par=0;
        for(int j=1; j<=n_bits_code; j++)
        {
            if(j&i) par^=(n_coded>>(n_bits_code-j))&1;
        }
        n_coded|=par<<(n_bits_code-i);
    }

    DBG(print_binary(n_coded, n_bits_code); printf("\n"));

    return n_coded;
}

int distance(int a, int b, int n_bits)
{
    int dist=0, ab=a^b;
    for(int i=0; i<n_bits; i++)
    {
        if(ab&1) dist++;
        ab>>=1;
    }
    return dist;
}

vector<int> hamming_decode_table(vector<int> &data, int n_bits_code)
{
    vector<int> table(1<<n_bits_code);
    for(int i=0; i<1<<n_bits_code; i++)
    {
        for(unsigned j=0; j<data.size(); j++)
        {
            if(distance(i, data[j], n_bits_code)<=1)
            {
                table[i]=j;
                break;
            }
        }
    }
    return table;
}

int main(int narg, char **arg)
{
    int n_bits=4, n_bits_code=7;
    vector<int> data(1<<n_bits);
    for(int i=0; i<1<<n_bits; i++) data[i]=hamming(i/*reverse(i, n_bits)*/, n_bits, n_bits_code);

    vector<int> decode=hamming_decode_table(data, n_bits_code);

    DBG(for(unsigned i=0; i<decode.size(); i++) { print_binary(i, n_bits_code); printf(" "); print_binary(decode[i], n_bits); printf("\n"); });

    string coded;
    while(cin >> coded)
    {
        if(coded.size()%7) { cout << "Error!" << endl; continue; }
        string decoded;

        int word=0, n_word=0;
        int dword=0, n_dword=0;
        bool error=false;
        for(unsigned i=0; i<coded.size(); i++)
        {
            word<<=1;
            word|=coded[i]-'0';
            n_word++;
            if(n_word==n_bits_code)
            {
                dword<<=n_bits;
                dword|=decode[word];
                n_dword++;
                if(n_dword==2)
                {
                    if(dword<32 || dword>127) { error=true; break; }
                    decoded+=char(dword);
                    n_dword=dword=0;
                }
                word=n_word=0;
            }
        }
        if(error)
            cout << "Error!" << endl;
        else
            cout << decoded << endl;
    }

    return 0;
}
