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

struct Position
{
    unsigned doc, line, word;
    Position(unsigned doc, unsigned line, unsigned word): doc(doc), line(line), word(word) { }
    Position() { }
};

void make_index(map<string, vector<Position> > &index)
{
    for(int i_doc=1; i_doc<=800; i_doc++)
    {
        printf("Indexing %d\n", i_doc);
        char doc_name[128];
        snprintf(doc_name, sizeof(doc_name), "c9_doc/%04d", i_doc);
        FILE *arch=fopen(doc_name, "r");
        int line=1;
        char *str=NULL;
        size_t max_str=0;
        int n_str;
        while((n_str=getline(&str, &max_str, arch))>0)
        {
            if(str[n_str-1]=='\n') str[--n_str]=0;
            DBG(printf("{%s}\n", str));

            int i_word=1;
            for(int i=0, last=0; i<n_str; )
            {
                while(isspace(str[i])) i++;
                if(!str[i]) break;
                last=i;
                while(str[i] && !isspace(str[i])) { str[i]=tolower(str[i]); i++; }
                str[i++]=0;
                index[string(&str[last])].push_back(Position(i_doc, line, i_word));
                DBG(printf("{%s} %d %d  ", &str[last], line, i_word));
                i_word++;
            }
            line++;
            DBG(printf("\n"));
        }
        fclose(arch);
    }

    // save index
    FILE *arch=fopen("/tmp/index", "w");
    for(map<string, vector<Position> >::iterator i=index.begin(); i!=index.end(); ++i)
    {
        short word_size=i->first.size();
        fwrite(&word_size, sizeof(short), 1, arch);
        fwrite(i->first.c_str(), 1, word_size, arch);
        unsigned vect_size=i->second.size();
        fwrite(&vect_size, sizeof(unsigned), 1, arch);
        fwrite(&i->second[0], sizeof(Position), vect_size, arch);
    }
    fclose(arch);
}

int main(int narg, char **arg)
{
    map<string, vector<Position> > index;
#if 0
    make_index(index);
#else
    // load index
    FILE *arch=fopen("/tmp/index", "r");
    short word_size;
    while(fread(&word_size, sizeof(short), 1, arch)==1)
    {
        char word[word_size+1];
        fread(word, 1, word_size, arch);
        word[word_size]=0;
        unsigned vect_size;
        fread(&vect_size, sizeof(unsigned), 1, arch);
        vector<Position> pos(vect_size);
        fread(&pos[0], sizeof(Position), vect_size, arch);
        index[word]=pos;
    }
    fclose(arch);    
#endif

    DBG(for(map<string, vector<Position> >::iterator i=index.begin(); i!=index.end(); ++i) printf("%9ld %s\n", i->second.size(), i->first.c_str()));

    int t;
    cin >> t;
    for(int it=0; it<t; it++)
    {
        int n;
        string str;
        cin >> str >> n;
        for(unsigned i=0; i<str.size(); i++) str[i]=tolower(str[i]);
        Position &pos=index[str][n-1];
        cout << pos.doc << "-" << pos.line << "-" << pos.word << endl;
    }
}
