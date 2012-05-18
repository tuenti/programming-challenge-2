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

struct Word
{
    string w;
    unsigned mask;
    int points;
    Word(string w, unsigned mask, int points): w(w), mask(mask), points(points) { }
    bool operator<(const Word &a) const { return points>a.points || (points==a.points && w<a.w); }
};

int points_letter[26]=
{
//  a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z
    1,  3,  3,  2,  1,  4,  2,  4,  1,  8,  5,  1,  3,  1,  1,  3, 10,  1,  1,  1,  1,  4,  4,  8,  4, 10
};

int main(int narg, char **arg)
{
    // read dict
    ifstream file("/tmp/descrambler_wordlist.txt");
    string word;
    vector<Word> dict[26];
    while(file >> word)
    {
        int points=0;
        unsigned mask=0;
        set<char> word_letters;
        for(unsigned i=0; i<word.size(); i++) { mask|=1<<(word[i]-'A'); word_letters.insert(word[i]); points+=points_letter[word[i]-'A']; }
        for(set<char>::iterator i=word_letters.begin(); i!=word_letters.end(); ++i)
            dict[int(*i)-'A'].push_back(Word(word, mask, points));
    }

    // sort dicts
    for(int i=0; i<26; i++) sort(dict[i].begin(), dict[i].end());

    int t;
    cin >> t;
    for(int it=0; it<t; it++)
    {
        string rack, board;
        cin >> rack >> board;

        unsigned mask=0;
        for(unsigned i=0; i<rack.size(); i++) mask|=1<<(rack[i]-'A');

        set<char> board_letters;
        for(unsigned i=0; i<board.size(); i++) board_letters.insert(board[i]);

        string best_word;
        int best_score=0;
        for(set<char>::iterator i=board_letters.begin(); i!=board_letters.end(); ++i)
        {
            unsigned tmp_mask=mask|(1<<(*i-'A'));
            vector<Word> &d=dict[int(*i)-'A'];
            DBG(printf("%c: \n", *i));
            for(unsigned j=0; j<d.size(); j++)
            {
                if( (d[j].mask & tmp_mask)==d[j].mask)
                {
                    // check exhaustive
                    vector<int> have(26);
                    for(unsigned k=0; k<rack.size(); k++) have[rack[k]-'A']++;
                    have[int(*i)-'A']++;

                    bool ok=true;
                    for(unsigned k=0; k<d[j].w.size(); k++)
                    {
                        if(!have[d[j].w[k]-'A']) { ok=false; break; }
                        have[d[j].w[k]-'A']--;
                    }
                    if(!ok) continue;

                    if(d[j].points > best_score || (d[j].points == best_score && d[j].w < best_word))
                    {
                        best_score=d[j].points;
                        best_word=d[j].w;
                    }
                    DBG(printf("%s ", d[j].w.c_str()));
                    break;
                }
            }
        }
        cout << best_word << " " << best_score << endl;
    }

    return 0;
}
