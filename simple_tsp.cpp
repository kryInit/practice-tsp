/* * * *
 * Todo
 * [] 2-opt
 * [] 3-opt
   [] n-opt                *
   [] simulated annealing  *
   [] optuna               *
                     * * * */

// default: 2.64764e+05
// default + simple_preprocessing: 1.56876e+05
// simple_solver: 4.15114e+04
// simple_solver + simple_preprocessing: 3.63035e+04

#include <bits/stdc++.h>
#include "random/xor_shift.h"
#include "simple_solver/simple_solver.h"
#include "utility/utility.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

void initialize();
void finalize();

void preprocessing();

Vec2 cities_coord[CITY_NUM]={};
int path[CITY_NUM]={};

int main() {
    initialize();
    preprocessing();
    simple_solver(path);
    finalize();
}

void preprocessing() {
    vector<pair<pair<int,int>, int>> v;
    rep(i,CITY_NUM) v.emplace_back(make_pair(cities_coord[i].x, cities_coord[i].y), i);
    sort(v.begin(), v.end());
    rep(i,CITY_NUM) path[i] = v[i].second;
}

void make_city() {
    rep(i,CITY_NUM) {
        int x = rand_range(MAX_COORD - MIN_COORD + 1) + MIN_COORD;
        int y = rand_range(MAX_COORD - MIN_COORD + 1) + MIN_COORD;
        cities_coord[i] = Vec2(x,y);
    }
}

void initialize() {
    init_rand_seed(112358);
    make_city();
    rep(i,CITY_NUM) path[i] = i;
}

void finalize() {
    cout << "total dist: " << scientific << setprecision(5) << calc_total_dist(path) << endl;
}

