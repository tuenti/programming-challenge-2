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

void infer()
{
    FILE *arch=fopen("/tmp/CANTTF.ppm", "r");
    //FILE *save=fopen("/tmp/CANTTF_save.ppm", "w");
    unsigned char tmp[128];
    fread(tmp, 1, 0x31, arch);
    //fwrite(tmp, 1, 0x31, save);
    //int color=0;

    unsigned byte=0, n_byte=0, total_bytes=0;

    while(fread(tmp, 1, 1, arch)==1)
    {
        byte<<=1;
        byte|=tmp[0]&1;
        n_byte++;
        if(n_byte==8)
        {
            n_byte=0;
            //printf("%2d %02x %c\n", total_bytes++, byte, byte);
            printf("%c", byte);
            byte=0;
            total_bytes++;
        }
        if(total_bytes==32) { printf("\n"); break; }

        //if(true || color==0) { tmp[0]&=3; tmp[0]*=0x3f; }
        //fwrite(tmp, 1, 1, save);
        //printf("%02x ", tmp[0]); if(color==2) printf("\n");
        //color++;
        //if(color==3) color=0;
    }
    fclose(arch);
    //fclose(save);
}

int main(int narg, char **arg)
{
    const char *k[3]={"ed8ce15da9b7b5e2ee70634cc235e363", // QR-code
                      "a541714a17804ac281e6ddda5b707952", // png comment
                      "62cd275989e78ee56a81f0265a87562e"};// steganography (see infer())

    //infer();

    string str;
    cin >> str;
    const char *keys[4]={k[0], k[1], k[2], &str[0]};

    hex(cout);
    for(unsigned i=0; i<32; i++)
    {
        int n=0;
        for(int j=0; j<4; j++)
        {
            char c[4]={'0', 'x', keys[j][i], 0};
            n+=strtoul(c, NULL, 16);
        }
        cout << (n&0xf);
    }
    cout << endl;
    return 0;
}
