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

struct LetterDescr
{
    char c;
    int pos[2];
    int puls;
} letter_descr[]=
{
    {'-', {3, 2}, 1},
    {' ', {0, 0}, 1},
    {'1', {0, 0}, 2},
    {'a', {0, 1}, 1},
    {'b', {0, 1}, 2},
    {'c', {0, 1}, 3},
    {'2', {0, 1}, 4},
    {'d', {0, 2}, 1},
    {'e', {0, 2}, 2},
    {'f', {0, 2}, 3},
    {'3', {0, 2}, 4},
    {'g', {1, 0}, 1},
    {'h', {1, 0}, 2},
    {'i', {1, 0}, 3},
    {'4', {1, 0}, 4},
    {'j', {1, 1}, 1},
    {'k', {1, 1}, 2},
    {'l', {1, 1}, 3},
    {'5', {1, 1}, 4},
    {'m', {1, 2}, 1},
    {'n', {1, 2}, 2},
    {'o', {1, 2}, 3},
    {'6', {1, 2}, 4},
    {'p', {2, 0}, 1},
    {'q', {2, 0}, 2},
    {'r', {2, 0}, 3},
    {'s', {2, 0}, 4},
    {'7', {2, 0}, 5},
    {'t', {2, 1}, 1},
    {'u', {2, 1}, 2},
    {'v', {2, 1}, 3},
    {'8', {2, 1}, 4},
    {'w', {2, 2}, 1},
    {'x', {2, 2}, 2},
    {'y', {2, 2}, 3},
    {'z', {2, 2}, 4},
    {'9', {2, 2}, 5},
    {'0', {3, 1}, 1},
    {0, {0, 0}, 0}
};

LetterDescr get_letter(char c)
{
    c=tolower(c);
    int i;
    for(i=0; i<letter_descr[i].c; i++) if(letter_descr[i].c==c) return letter_descr[i];
    return letter_descr[i];
}

int main(int narg, char **arg)
{
    int t;
    cin >> t;
    size_t max_str=0;
    char *str=NULL;
    getline(&str, &max_str, stdin);
    for(int it=0; it<t; it++)
    {
        int n_str=getline(&str, &max_str, stdin);
        if(str[n_str-1]=='\n') str[--n_str]=0;

        int pos[2]={3, 1};
        bool mays=false;
        int time=0;

        for(int i=0; str[i]; i++)
        {
            char c=str[i];
            LetterDescr let;

            DBG(printf("%d  %s\n", time, &str[i]));

            // mays
            if(isalpha(c) && ((isupper(c) && !mays) || (islower(c) && mays)))
            {
                DBG(printf("MAYS\n"));
                let=get_letter('-');
                mays=isupper(c);
                i--;
            }
            else
                let=get_letter(c);

            // move
            bool moved=false;
            while(pos[0]!=let.pos[0] || pos[1]!=let.pos[1])
            {
                moved=true;
                if(pos[0]!=let.pos[0] && pos[1]!=let.pos[1])
                {
                    // diag
                    DBG(printf("DIAG\n"));
                    time+=350;
                    if(pos[0]<let.pos[0]) pos[0]++; else pos[0]--;
                    if(pos[1]<let.pos[1]) pos[1]++; else pos[1]--;
                }
                else if(pos[0]!=let.pos[0])
                {
                    // vert
                    DBG(printf("VERT\n"));
                    time+=300;
                    if(pos[0]<let.pos[0]) pos[0]++; else pos[0]--;
                }
                else
                {
                    // hor
                    DBG(printf("HOR\n"));
                    time+=200;
                    if(pos[1]<let.pos[1]) pos[1]++; else pos[1]--;
                }
            }

            // press
            for(int j=0; j<let.puls; j++)
            {
                DBG(printf("PULS\n"));
                if(!moved && i) { time+=500; moved=true; }
                time+=100;
            }
        }
        cout << time << endl;
    }

    return 0;
}
