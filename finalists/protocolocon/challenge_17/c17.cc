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

const double eps=1e-9;

using namespace std;

struct Ingredient
{
    int type;
    double min_ang, max_ang;
    Ingredient(int type, double min_ang, double max_ang): type(type), min_ang(min_ang), max_ang(max_ang) { }
    Ingredient() { }
};

inline double distance(double a[2], double b[2])
{
    return sqrt( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) );
}

inline double angle(double a[2], double b[2])
{
    return atan2( a[1]-b[1], a[0]-b[0] );
}

inline double vectorial(double v[2], double w[2])
{
    return v[0]*w[1]-v[1]*w[0];
}

inline double rot(double angle)
{
    while(angle<-M_PI) angle+=2*M_PI;
    while(angle>M_PI) angle-=2*M_PI;
    return angle;
}

bool occupied(vector<Ingredient> &ing, double angle, double &inc)
{
    while(angle<-M_PI) angle+=M_PI;
    while(angle>0) angle-=M_PI;
    double angle2=angle+M_PI;

    for(unsigned i=0; i<ing.size(); i++)
    {
        Ingredient &g=ing[i];
        if(g.min_ang>g.max_ang)
        {
            if(angle>g.min_ang || angle<g.max_ang)
            {
                inc=g.max_ang-angle+eps;
                while(inc<eps) inc+=2*M_PI;
                return true;
            }
            if(angle2>g.min_ang || angle2<g.max_ang)
            {
                inc=g.max_ang-angle2+eps;
                while(inc<eps) inc+=2*M_PI;
                return true;
            }
        }
        else
        {
            if(angle>g.min_ang && angle<g.max_ang)
            {
                inc=g.max_ang-angle+eps;
                return true;
            }
            if(angle2>g.min_ang && angle2<g.max_ang)
            {
                inc=g.max_ang-angle2+eps;
                return true;
            }
        }
    }
    return false;
}

double next(vector<Ingredient> &ing, double angle)
{
    double min_dist=INFINITY;
    for(unsigned i=0; i<ing.size(); i++)
    {
        double a=ing[i].min_ang;
        while(a>angle) a-=M_PI;
        while(a<angle) a+=M_PI;
        min_dist=min(min_dist, a-angle);
    }
    return angle+min_dist+eps;
}

bool valid_positions(vector<Ingredient> &ing, double angle)
{
    while(angle<-M_PI) angle+=M_PI;
    while(angle>0) angle-=M_PI;
    double angle2=angle+M_PI;

    vector<int> ingred(11);
    for(unsigned i=0; i<ing.size(); i++)
    {
        Ingredient &g=ing[i];
        if(g.min_ang>=angle && g.min_ang<=angle2) ingred[g.type]++; else ingred[g.type]--;
    }
    for(unsigned i=0; i<ingred.size(); i++) if(ingred[i]) return false;
    return true;
}

int main(int narg, char **arg)
{
    int t;
    cin >> t;
    for(int it=0; it<t; it++)
    {
        bool odd_ing=false, center_ing=false;
        vector<Ingredient> ing;

        double center[2], radius;
        cin >> center[0] >> center[1] >> radius;
        int n_types;
        cin >> n_types;
        for(int i=0; i<n_types; i++)
        {
            string type;
            int n_vertex, n_of_type;
            cin >> type >> n_vertex >> n_of_type;

            if(n_of_type&1) odd_ing=true;

            for(int j=0; j<n_of_type; j++)
            {
                double c[2], v[n_vertex][2];
                cin >> c[0] >> c[1] >> v[0][0] >> v[0][1];
                double r=distance(c, v[0]), a=angle(v[0], c);
                for(int k=1; k<n_vertex; k++)
                {
                    double aa=a+double(k)*2*M_PI/double(n_vertex);
                    v[k][0]=c[0]+r*cos(aa);
                    v[k][1]=c[1]+r*sin(aa);
                }

                DBG(printf("%s:\n", type.c_str()); for(int k=0; k<n_vertex; k++) printf("  %2d %6.1f %6.1f\n", k, v[k][0], v[k][1]); printf("\n"));

                // check if ingredient occupies pizza's center, and angle segment
                bool inverse=false;
                double minim=INFINITY, min_ang=INFINITY, max_ang=-INFINITY;
                for(int k=0; k<n_vertex; k++)
                {
                    int kk=k+1; if(kk==n_vertex) kk=0;
                    double v1[2]={ v[kk][0]-v[k][0], v[kk][1]-v[k][1] };
                    double v2[2]={ center[0]-v[k][0], center[1]-v[k][1] };
                    double esc=vectorial(v1, v2);
                    minim=min(minim, esc);

                    double ang[2]={ angle(v[k], center), angle(v[kk], center) };
                    if(esc>eps && ang[0]>ang[1]) inverse=true;
                    min_ang=min(min_ang, ang[0]);
                    max_ang=max(max_ang, ang[1]);
                    DBG(printf("%9.3f  %9.3f %9.3f\n", esc, ang[0], ang[1]));
                }
                if(minim>eps) center_ing=true;
                if(inverse) swap(min_ang, max_ang);
                ing.push_back(Ingredient(i, min_ang, max_ang));
            }
        }

        bool possible=false;
        if(!odd_ing && !center_ing)
        {
            // find an angle to cut
            if(ing.empty()) possible=true;
            else
            {
                DBG(
                    for(unsigned i=0; i<ing.size(); i++)
                        printf("%2d %d %9.3f %9.3f   %9.3f %9.3f\n", i, ing[i].type, ing[i].min_ang, ing[i].max_ang, rot(ing[i].min_ang+M_PI), rot(ing[i].max_ang+M_PI)));

                double angle=ing[0].min_ang+eps, angle_end=angle+M_PI+eps;
                while(angle<angle_end)
                {
                    double inc;
                    while(angle<angle_end && occupied(ing, angle, inc)) { DBG(printf("%9.6f inc\n", inc)); angle+=inc; }
                    if(!(angle<angle_end)) break;

                    // free angle (check ingredient positions)
                    DBG(double aa=angle; while(aa>M_PI) aa-=M_PI; printf("Free %9.3f\n", aa));
                    if(valid_positions(ing, angle)) { possible=true; break; }

                    // goto next ingredient
                    angle=next(ing, angle);
                }
            }
        }
        cout << "Case #" << (it+1) << ": " << (possible?"TRUE":"FALSE") << endl;
    }
    return 1;
}
