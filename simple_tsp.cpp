/* * * *
 * Todo
 * [x] 2-opt
 * [] 3-opt
   [] n-opt                *
   [] simulated annealing  *
   [] optuna               *
                     * * * */

// default                                     : 2.64764e+05
// default + simple_preprocessing              : 1.56876e+05
// simple_solver                               : 4.15114e+04
// simple_solver + simple_preprocessing        : 3.63035e+04
// 2-opt                                       : 1.92137e+04
// 2-opt + simple_preprocessing                : 1.92300e+04
// simple_solver(1sec) + 2-opt(2sec) + sp      : 1.89941e+04
// simple_solver(1.5sec) + 2-opt(1.5sec) + sp  : 1.90244e+04
// simple_solver(2sec) + 2-opt(1sec) + sp      : 1.88177e+04

#include <bits/stdc++.h>
#include "random/xor_shift.h"
#include "utility/utility.h"
#include "solvers/simple_solver/simple_solver.h"
#include "solvers/2-opt/2-opt.h"
#include "solvers/preprocessing/simple_preprocessing.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

void initialize();
void finalize();

Vec2 cities_coord[CITY_NUM]={};
int path[CITY_NUM]={};

int main() {
    initialize();
    simple_preprocessing(path);
    simple_solver(path, 2000);
    simple_solver_using_2_opt(path, 1000);
    finalize();
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

void check() {
    int cnt[CITY_NUM]={};
    rep(i,CITY_NUM) cnt[path[i]]++;
    rep(i,CITY_NUM) if (cnt[i] != 1) {
        cerr << "cities are duplicated" << endl;
        exit(1);
    }
}

void finalize() {
    check();
    cout << "total dist: " << scientific << setprecision(5) << calc_total_dist(path) << endl;
}

