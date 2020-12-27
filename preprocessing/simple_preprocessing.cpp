#include <vector>
#include "../utility/utility.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

void simple_preprocessing(int path[CITY_NUM]) {
    vector<pair<pair<int,int>, int>> v;
    rep(i,CITY_NUM) v.emplace_back(make_pair(cities_coord[i].x, cities_coord[i].y), i);
    sort(v.begin(), v.end());
    rep(i,CITY_NUM) path[i] = v[i].second;
}


