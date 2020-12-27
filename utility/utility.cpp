#include <iostream>
#include <cmath>
#include "utility.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

int square_dist(Vec2 a, Vec2 b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx*dx + dy*dy;
}
double dist(Vec2 a, Vec2 b) { return sqrt((double)square_dist(a,b)); }

double calc_total_dist(int path[CITY_NUM]) {
#ifndef NDEBUG
    int cnt[CITY_NUM]={};
    rep(i,CITY_NUM) cnt[path[i]]++;
    rep(i,CITY_NUM) if (cnt[i] != 1) {
        cerr << "cities are duplicated" << endl;
        exit(1);
    }
#endif
    double total_dist = 0;
    rep(i,CITY_NUM-1) total_dist += dist(cities_coord[path[i]], cities_coord[path[i+1]]);
    total_dist += dist(cities_coord[path[CITY_NUM-1]], cities_coord[0]);
    return total_dist;
}
