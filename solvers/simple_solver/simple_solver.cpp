#include <bits/stdc++.h>
#include "../../random/xor_shift.h"
#include "../../time/time_manager.hpp"
#include "simple_solver.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)


extern Vec2 cities_coord[CITY_NUM];

void simple_solver(int path[CITY_NUM], const unsigned int ms_time_limit) {
    time_manager tm(ms_time_limit);
    double best_total_dist = calc_total_dist(path);
    int loop_count = 0;
    while(tm.is_within_time_limit()) {
        loop_count++;
        unsigned int i = rand_range(CITY_NUM), j = rand_range(CITY_NUM);
        if (i == j) { j = rand_range(CITY_NUM); }
        swap(path[i], path[j]);
        double tmp_total_dist = calc_total_dist(path);
        if (best_total_dist > tmp_total_dist) {
            best_total_dist = tmp_total_dist;
        } else swap(path[i], path[j]);
    }
    cout << "loop count: " << loop_count << endl;
}

