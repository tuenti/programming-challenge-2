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
#include <iomanip>
#include <cassert>

#include "c20_/openssl-0.9.8o/crypto/aes/aes.h"

#include "mcrypt_def.h"
#include "des.c"

#define DBG(x, arg...)       //x, ##arg

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BROWN "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int first_key, last_key;
unsigned char *aes_msg;
int n_aes_msg;

using namespace std;

struct Msg
{
    bool deciphered;
    string msg;
    vector<pair<string, bool> > keys;
};

unsigned char nibble(char c)
{
    if(c<='9') return c-'0'; else return c-'a'+10;
}

char asc(char c)
{
    if(c<32 || c>=127) return '.'; else return c;
}

char parity(char x)
{
    char dev=x, n=0;
    for(int i=0; i<7; i++)
    {
        if(x&1) n++;
        x>>=1;
    }
    return dev | (n&1)<<7;
}

void print(string &str)
{
    for(unsigned i=0; i<str.size(); i++)
        if(str[i]<32 || str[i]>=127) printf(BLUE"%02x"RESET, (unsigned char)str[i]); else printf("%c", str[i]);
}

void print_string(char *buffer, int n_buffer)
{
    for(int j=0; j<256; j+=16)
    for(int i=0; i<8; i++)
    {
        int n_bits=i, bits=0;
        for(int x=0; x<n_buffer; x++)
        {
            bits<<=8;
            bits|=(unsigned char)buffer[x];
            n_bits+=8;

            while(n_bits>=8)
            {
                printf("%c", asc( j + ( (bits>>(n_bits-8))&0xff ) ));
                n_bits-=8;
            }
        }
        printf("\n");
    }
}

void binary_analysis(char *buffer, int n_buffer)
{
    // print in binary
    string bin;
    for(int x=0; x<n_buffer; x++)
    {
        int c=buffer[x];
        for(int xx=0; xx<8; xx++)
        {
            bin+=char('0'+((c>>7)&1));
            c<<=1;
        }
        //printf(" ");
    }
    // remove trailing 0
    while(!bin.empty() && bin[bin.size()-1]=='0') bin=bin.substr(0, bin.size()-1);

    //if(bin.size()>40<<3) return;

    int counter=0;
    for(unsigned i=0; i<bin.size(); i++)
    {
        if(bin.size()-i > 12)
        {
            if(bin.substr(i, 7)=="0010000") { counter++; i+=6; }
        }
    }
    //if(counter<10) return;

    const char *dest="When 900 years old, you reach... Look as good, you will not.";
    printf("           "); for(unsigned i=0; dest[i]; i++) printf("    %c   ", dest[i]); printf("\n");

    printf("   %3ld #%2d  {", bin.size()>>3, counter);
    unsigned m=0;


    for(unsigned i=0; i<bin.size(); i++)
    {
        if(bin.size()-i > 12)
        {
            //if(bin.substr(i, 14)=="11011111101111") { printf(RED); m=i+14; }
            if(bin.substr(i, 7)=="0010000") { printf(RED); m=i+7; }
            //if(bin.substr(i, 7)=="1101111") { printf(GREEN); m=i+7; }
            //if(bin.substr(i, 8)=="01010101") { printf(RED); m=i+7; }
            //if(bin.substr(i, 8)=="01110011") { printf(GREEN); m=i+7; }
            //if(bin.substr(i, 8)=="01100101") { printf(BLUE); m=i+7; }
        }
        if(i==m) printf(RESET);
        printf("%c", bin[i]);
    }
    printf("}\n");

#if 0
    for(int x=bin.size()>>1; x>32; x--)
    {
        for(unsigned xx=0; xx<bin.size()-(x<<1); xx++)
        {
            string token=bin.substr(xx, x);
            if(bin.find(token, xx+x)!=string::npos)
            {
                printf("  -> %s\n", token.c_str());
                x=0;
                break;
            }
        }
    }
#endif
}


void break_msg(vector<Msg> &messages)
{
    unsigned char passwd[256], buffer_cpy[1024];
    memset(passwd, 0, sizeof(passwd));
    MCRYPT td;

    char c[]={' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
              'v', 'w', //'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-', '.',
              0};

    int counter=0;
    passwd[4]=passwd[5]=passwd[6]=passwd[7]='0';
    for(int i=0; passwd[0]=c[i]; i++) if(passwd[0]&1)
        for(int j=0; passwd[1]=c[j]; j++) if(passwd[1]&1)
            for(int k=0; passwd[2]=c[k]; k++) if(passwd[2]&1)
                for(int q=0; passwd[3]=c[q]; q++) if(passwd[3]&1)
                {
                    DES_KEY key;
                    _mcrypt_set_key(&key, passwd, 8);

                    for(unsigned i_messages=0; i_messages<messages.size(); i_messages++)
                    {
                        Msg &msg=messages[i_messages];
                        if(msg.deciphered) continue;
                        for(unsigned imsg=0; imsg<msg.keys.size(); imsg++)
                        {
                            if(msg.keys[imsg].second) continue; // already deciphered
                            string &key_=msg.keys[imsg].first;

                            ((unsigned long long *)buffer_cpy)[0] = ((unsigned long long *)key_.c_str())[0];
                            _mcrypt_decrypt(&key, buffer_cpy);
                            if(buffer_cpy[0]=='K' && buffer_cpy[1]=='e' && buffer_cpy[2]=='y' && buffer_cpy[3]=='=')
                            {
                                buffer_cpy[8]=0;
                                string str=buffer_cpy;
                                for(unsigned x=1; x<key_.size()>>3; x++)
                                {
                                    ((unsigned long long *)buffer_cpy)[0] = ((unsigned long long *)key_.c_str())[x];
                                    _mcrypt_decrypt(&key, buffer_cpy);
                                    str+=string(buffer_cpy);
                                }
                                for(unsigned x=0; x<str.size(); x++)
                                {
                                    if(str[x]<32 || str[x]>127) { str=str.substr(0, x); break; }
                                }
                                //printf("{%-34s} %s %4d %4d %4d\n", str.c_str(), passwd, i_messages, imsg, ++counter);

                                // extract key
                                string key__=str.substr(4, 16);
                                key_=key__;
                                msg.keys[imsg].second=true;



                                unsigned char buffer[1024];
                                AES_KEY aes_key;
                                AES_set_decrypt_key(key_.c_str(), 128, &aes_key);
                                for(int i=0; i<msg.msg.size(); i+=16)
                                    AES_decrypt((unsigned char*)msg.msg.c_str()+i, buffer+i, &aes_key);

                                int imax;
                                for(imax=msg.msg.size()-1; imax>=0; imax--) if(buffer[imax]>=32) break;

                                bool possible=true;
                                for(int i=0; i<imax; i++) if(buffer[i]<32 || buffer[i]>127) { possible=false; break; }
                                if(possible)
                                {
                                    msg.deciphered=true;
                                    msg.msg=string((char*)buffer, imax+1);
                                    //string result((char*)buffer, msg.msg.size()); print(result); printf("\n"); fflush(stdout);
                                }
                            }
                        }
                    }
               }
}

// string modification functions
string set_parity_bit(const string &key)
{
    DBG(printf("KEY: set_parity_bit\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++) out+=key[x]|0x80;
    return out;
}

string calculate_parity_bit(const string &key)
{
    DBG(printf("KEY: calculate_parity_bit\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++) out+=parity(key[x]);
    return out;
}

string remove_parity_compact(const string &key, int param)
{
    if(!param) return key;
    if(param==1) return set_parity_bit(key);
    if(param==2) return calculate_parity_bit(key);
    DBG(printf("KEY: remove_parity_compact: %d\n", param));

    string out;
    unsigned int bits=0, n_bits=0;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=7;
        bits|=(unsigned char)(key[x]&0x7f);
        n_bits+=7;
        while(n_bits>=8)
        {
            out+=char(bits>>(n_bits-8));
            n_bits-=8;
        }
    }
    if(n_bits) out+=char(bits<<(8-n_bits));
    return out;
}

string remove_parity_compact_back(const string &key, int param)
{
    if(!param) return key;

    DBG(printf("KEY: remove_parity_compact_back: %d\n", param));
    string out;

    if(param==1)
    {
        for(unsigned x=0; x<key.size(); x++) out+=key[x]&0xfe;
        return out;
    }
    if(param==2)
    {
        for(unsigned x=0; x<key.size(); x++) out+=key[x]|1;
        return out;
    }

    unsigned int bits=0, n_bits=0;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=7;
        bits|=(unsigned char)((key[x]>>1)&0x7f);
        n_bits+=7;
        while(n_bits>=8)
        {
            out+=char(bits>>(n_bits-8));
            n_bits-=8;
        }
    }
    if(n_bits) out+=char(bits<<(8-n_bits));
    return out;
}

string key_negate(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_negate\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++) out+=~key[x];
    return out;
}

string reset_parity(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: reset_parity\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++) out+=key[x]&0x7f;
    return out;
}

string key_invert_7(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_invert_7\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++)
    {
        unsigned char c=key[x], d=0;
        for(int i=0; i<7; i++) { d<<=1; d|=c&1; c>>=1; }
        out+=d;
    }
    return out;
}

string key_invert_8(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_invert_8\n"));

    string out;
    for(unsigned x=0; x<key.size(); x++)
    {
        unsigned char c=key[x], d=0;
        for(int i=0; i<8; i++) { d<<=1; d|=c&1; c>>=1; }
        out+=d;
    }
    return out;
}

string key_expand(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_expand\n"));

    string out;
    unsigned int bits=0, n_bits=0;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=8;
        bits|=(unsigned char)(key[x]&0xff);
        n_bits+=8;
        while(n_bits>=7)
        {
            out+=char((bits>>(n_bits-7))&0x7f);
            n_bits-=7;
        }
    }
    if(n_bits) out+=char((bits<<(7-n_bits))&0x7f);
    return out;
}

string key_rotate(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_rotate: %d\n", param));

    string out;
    unsigned int bits=0, n_bits=param;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=8;
        bits|=(unsigned char)(key[x]&0xff);
        n_bits+=8;
        while(n_bits>=8)
        {
            out+=char((bits>>(n_bits-8))&0xff);
            n_bits-=8;
        }
    }
    if(n_bits) out+=char(bits<<(8-n_bits));
    return out;
}

string key_ror(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: key_ror: %d\n", param));

    string out;
    for(unsigned x=0; x<key.size(); x++)
    {
        out+=(char)( ((unsigned char)key[x])<<param | ((unsigned char)key[x])>>(8-param) );
    }
    return out;
}

string add_16_zero(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: add 16 zero: %d\n", param));

    if(key.size()==16)
        return key+"0000000000000000";
    if(key.size()==14)
        return key+"000000000000000000";

    string out=key;
    while(out.size()<32) out+='0';
    return out;
}

string only_even(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: only_even\n"));

    string out;
    unsigned int bits=0, n_bits=0;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=4;
        unsigned char c=key[x];
        bits|=(unsigned char)( (c&2)>>1 | (c&8)>>2 | (c&32)>>3 | (c&128)>>4 );
        n_bits+=4;
        while(n_bits>=8)
        {
            out+=char(bits>>(n_bits-8));
            n_bits-=8;
        }
    }
    if(n_bits) out+=char(bits<<(8-n_bits));
    return out;
}

string compact_5(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: compact 5\n"));

    string str("0123456789abcdefghijklmnopqrstuv");

    string out;
    for(unsigned x=0; x<key.size(); x++) out+=char(str.find(key[x]));
    return out;
}

string remove_up(const string &key, int param)
{
    if(!param) return key;
    DBG(printf("KEY: remove up: %d\n", param));

    string out;
    unsigned int bits=0, n_bits=0;
    for(unsigned x=0; x<key.size(); x++)
    {
        bits<<=8-param;
        bits|=(unsigned char)(key[x]&  (  (1<<(8-param))-1  )  );
        n_bits+=8-param;
        while(n_bits>=8)
        {
            out+=char(bits>>(n_bits-8));
            n_bits-=8;
        }
    }
    if(n_bits) out+=char(bits<<(8-n_bits));
    return out;
}

// decipher function
string decipher(const string &key_, int param)
{
    int size=param&3, key_size;
    switch(size)
    {
    case 0: key_size=128; break;
    case 1: key_size=192; break;
    case 2: key_size=256; break;
    case 3: return string();
    }

    unsigned char buffer[1024];
    //memset(buffer, 0, sizeof(buffer));
    AES_KEY aes_key;
    AES_set_decrypt_key(key_.c_str(), key_size, &aes_key);
    for(int i=0; i<n_aes_msg; i+=16)
        AES_decrypt(aes_msg+i, buffer+i, &aes_key);

    //for(int i=0; i<n_aes_msg; i++) printf("%02x ", buffer[i]); printf("\n");
    return string((char*)buffer, n_aes_msg);


#if 0
    int size=param&3;
    if(size==3) return string();

    DBG(printf("KEY: decipher: %d -> %d\n", param, size));

    string key=key_;
    if(param&4)
    {
        // fill with zero
        while(key.size()<32) key+='0';
    }

    const char *algo;
    switch(size)
    {
    case 0: // 128
        algo="rijndael-128";
        break;
    case 1: // 192
        algo="rijndael-192";
        break;
    case 2: // 256
        algo="rijndael-256";
        break;
    }

    char command[1024];
    snprintf(command, sizeof(command), "/dev/shm/key__%d", first_key);

    ofstream keyfile(command);
    keyfile << hex << setfill('0');
    for(unsigned x=0; x<key.size(); x++) keyfile << setw(2) << int((unsigned char)key[x]);
    keyfile << endl;
    keyfile.close();

    {
        snprintf(command, sizeof(command),
                 "mcrypt -d -b -q -a %s -m ecb -o hex -f /dev/shm/key__%d /dev/shm/msg__%d.nc", algo, first_key, first_key);

        system(command);

        snprintf(command, sizeof(command), "/dev/shm/msg__%d", first_key);

        FILE *arch=fopen(command, "r");
        char buffer[1024];
        int n_buffer=fread(buffer, 1, 1024, arch);
        fclose(arch);
        unlink(command);

        return string(buffer, n_buffer);
    }
#endif
}

struct StringTransform
{
    int n_bits;
    string (*func)(const string &, int param);
};

StringTransform key_transform[]=
{
    //{ 3, key_rotate },
    //{ 1, key_negate },
    //{ 1, key_invert_7 },
    //{ 1, compact_5 },
    { 3, key_ror },
    { 2, remove_up },
    { 2, remove_parity_compact },
    //{ 2, remove_parity_compact_back },
    //{ 1, add_16_zero },
    //{ 1, key_invert_8 },
    //{ 1, only_even },
    //{ 1, key_expand },
    { 0, NULL }
};
const int key_comb=0;//13;

StringTransform decipher_transform[]=
{
    { 1, decipher },
    { 0, NULL }
};
const int decipher_comb=0;

StringTransform transform_transform[]=
{
    //{ 3, key_rotate },
    //{ 3, key_ror },
    //{ 1, key_negate },
    { 1, key_invert_7 },
    { 2, remove_parity_compact },
    { 1, key_invert_8 },
    { 1, key_expand },
    { 1, reset_parity },
    { 0, NULL }
};
const int transform_comb=0; //13;

void infer(vector<Msg> &messages)
{
    const char *msg[]={
        "Use the Force, Luke... Use the Force.",
        "I am your father",
        "I find your lack of faith disturbing.",
        "These aren't the droids you're looking for",
        "When 900 years old, you reach... Look as good, you will not."};

    Msg &message=messages[1];
    const char *search="your ";

#if 0
    // test
    // mcrypt -b -o asis -m ecb -a rijndael-128 /tmp/m1
    message.msg="\x1d\xc9\xf3\xe3\x44\xd8\x07\x22\x41\x42\x98\xbe\x55\xf8\x46\xff\x3a\xa6\x4a\x36\x04\xe4\x64\x8f\x58\x17\xa8\x88\x94\xd2\x24\xa7";
    message.keys[0].first="1234";
    search="your";
#endif

    char filename[256];
    snprintf(filename, sizeof(filename), "/dev/shm/msg__%d.nc", first_key);
    ofstream file(filename);
    file << message.msg;
    file.close();

    snprintf(filename, sizeof(filename), "/dev/shm/msg__%d.dc", first_key);
    ofstream file2(filename);
    file2 << message.msg;
    file2.close();

    aes_msg=(unsigned char*)message.msg.c_str();
    n_aes_msg=int(message.msg.size());

    set<string> no_repeat_key;

    int counter=0;
    for(unsigned i_test=first_key/*0*/; i_test<last_key/*message.keys.size()*/; i_test++)
    {
        string &key=message.keys[i_test].first;
        no_repeat_key.clear();
        printf("Key %d\n", i_test);

        for(int i_key=0; i_key< 1 << key_comb; i_key++)
        {
            // transform key
            int i_key_=i_key;
            string key_modified=key;
            for(int test_key=0; key_transform[test_key].n_bits; test_key++)
            {
                key_modified=key_transform[test_key].func(key_modified, i_key_ & ((1<<key_transform[test_key].n_bits)-1));
                i_key_>>=key_transform[test_key].n_bits;
            }
            if(key_modified.empty()) continue;

            if(no_repeat_key.find(key_modified)!=no_repeat_key.end()) continue;
            no_repeat_key.insert(key_modified);

            DBG(print(key_modified); printf("\n"));

            for(int i_decipher=0; i_decipher< 1 << decipher_comb; i_decipher++)
            {
                // decipher
                int i_decipher_=i_decipher;
                string decoded;
                for(int test_decipher=0; decipher_transform[test_decipher].n_bits; test_decipher++)
                {
                    decoded=decipher_transform[test_decipher].func(key_modified, i_decipher_ & ((1<<decipher_transform[test_decipher].n_bits)-1));
                    i_decipher_>>=decipher_transform[test_decipher].n_bits;
                }
                if(decoded.empty()) continue;

                DBG(print(decoded); printf("\n"));

                for(int i_transform=0; i_transform< 1 << transform_comb; i_transform++)
                {
                    // transform final
                    int i_transform_=i_transform;
                    string decoded_modified=decoded;
                    for(int test_transform=0; transform_transform[test_transform].n_bits; test_transform++)
                    {
                        decoded_modified=transform_transform[test_transform].func(decoded_modified, i_transform_ & ((1<<transform_transform[test_transform].n_bits)-1));
                        i_transform_>>=transform_transform[test_transform].n_bits;
                    }
                    if(decoded_modified.empty()) continue;

                    // search needle
                    if(decoded_modified.find(search)!=string::npos)
                    {
                        printf("FOUND: %d %08x %08x %08x {", i_test, i_key, i_decipher, i_transform);
                        print(decoded_modified);
                        printf("} {");
                        print(key_modified);
                        printf("}\n");
                        counter++;
                    }
                }
            }
        }
    }
    printf("Found: %d\n", counter);
}

int main(int narg, char **arg)
{
    if(narg==3) { first_key=atoi(arg[1]); last_key=atoi(arg[2]); } else { first_key=0; last_key=1000; }

    vector<Msg> messages;
    int i_str=0;
    string str;
    while(cin >> str)
    {
        int msg_end=str.find(':');

        string decoded;
        string msg=str.substr(0, msg_end);
        for(unsigned i=0; i<msg.size(); i+=2)
        {
            unsigned char c=nibble(msg[i])<<4 | nibble(msg[i+1]);
            decoded+=char(c);
        }
        //printf("msg%d size %ld\n", i_str, decoded.size());

        Msg m;
        m.deciphered=false;
        m.msg=decoded;

        char filename[1024];
        snprintf(filename, sizeof(filename), "/dev/shm/msg%d.nc", i_str);
        i_str++;
        ofstream file(filename);
        file << m.msg;
        file.close();

        while(true)
        {
            msg_end++;
            int next=str.find('~', msg_end);
            string coded=str.substr(msg_end, next-msg_end);

            decoded="";
            for(unsigned i=0; i<coded.size(); i+=2)
            {
                unsigned char c=nibble(coded[i])<<4 | nibble(coded[i+1]);
                decoded+=char(c);
            }
            m.keys.push_back(make_pair(decoded, false));

            if(next==string::npos) break;
            msg_end=next;
        }
        messages.push_back(m);
    }

#if 1
    // save keys and messages
    break_msg(messages);

    for(unsigned i=0; i<messages.size(); i++)
    {
        if(!messages[i].deciphered) { fprintf(stderr, "Warning: msg not decoded\n"); abort(); }
        cout << messages[i].msg << endl;
    }
    return 0;
    ofstream file("keys.txt");
    for(unsigned i=0; i<messages.size(); i++)
    {
        file << i << endl;
        Msg &message=messages[i];
        for(unsigned j=0; j<message.keys.size(); j++)
        {
            if(!message.keys[j].second) { fprintf(stderr, "Warning: key not decoded\n"); abort(); }
            string &key=message.keys[j].first;

            file << key << endl;
        }
    }
    file.close();
#else
    // load keys
    ifstream file("keys.txt");
    int imsg, cmsg=0;
    while(file >> imsg)
    {
        assert(imsg==cmsg);
        cmsg++;
        for(int i=0; i<1000; i++)
        {
            file >> messages[imsg].keys[i].first;
            messages[imsg].keys[i].second=true;
        }
    }
    file.close();
#endif

    infer(messages);
    return 0;
}
