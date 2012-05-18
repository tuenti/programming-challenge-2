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

double distance_(vector<double> &a, vector<double> &b)
{
    double dist=0;
    for(unsigned i=0; i<a.size(); i++)
    {
        double diff=a[i]-b[i];
        dist+=diff*diff;
    }
    return sqrt(dist);
}

double distance(vector<double> &f, vector<vector<double> > &v)
{
    double dist=INFINITY;
    for(unsigned i=0; i<v.size(); i++)
    {
        double d=distance_(f, v[i]);
        dist=min(dist, d);
    }
    return dist;
}

int main(int narg, char **arg)
{
    // neighbors approach is working (neural network or logistic regression seems not necesary)
    int n_train, n_class, n_feature;
    cin >> n_train >> n_class >> n_feature;

    vector<vector<double> > good, bad;
    for(int i=0; i<n_train; i++)
    {
        char type;
        cin >> type;

        double sum=0;
        vector<double> feats(n_feature);
        for(int j=0; j<n_feature; j++) { cin >> feats[j]; sum+=feats[j]; }

        // normalize
        for(int j=0; j<n_feature; j++) feats[j]/=sum;

        if(type=='S') good.push_back(feats); else bad.push_back(feats);
    }

    int counter=0;
    for(int i=0; i<n_class; i++)
    {
        int sum=0;
        vector<double> feats(n_feature);
        for(int j=0; j<n_feature; j++) { cin >> feats[j]; sum+=feats[j]; }

        for(int j=0; j<n_feature; j++) feats[j]/=double(sum);

        double dist[2]={distance(feats, good), distance(feats, bad)};
        DBG(printf("%9.2f %9.2f\n", dist[0], dist[1]));
        if(dist[0]>dist[1]) counter+=sum;
    }
    cout << counter << endl;
    return 0;
}
