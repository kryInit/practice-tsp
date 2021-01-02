#include <bits/stdc++.h>
#include "random/xor_shift.h"
#include "time/time_manager.hpp"
#include "swap.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

void swap(int path[CITY_NUM], const unsigned int ms_time_limit) {
    time_manager tm(ms_time_limit);
    int loop_count = 0;
    while(tm.is_within_time_limit()) {
        loop_count++;
        unsigned int i = rand_range(CITY_NUM), j = rand_range(CITY_NUM);
        if (i == j) { j = rand_range(CITY_NUM); }

        unsigned int prev_i = (i == 0 ? CITY_NUM-1 : i-1);
        unsigned int next_i = (i == CITY_NUM-1 ? 0 : i+1);
        unsigned int prev_j = (j == 0 ? CITY_NUM-1 : j-1);
        unsigned int next_j = (j == CITY_NUM-1 ? 0 : j+1);

        double diff_dist = dist(cities_coord[path[prev_i]], cities_coord[path[j]]) +
                           dist(cities_coord[path[j]], cities_coord[path[next_i]]) +
                           dist(cities_coord[path[prev_j]], cities_coord[path[i]]) +
                           dist(cities_coord[path[i]], cities_coord[path[next_j]]) -
                           dist(cities_coord[path[prev_i]], cities_coord[path[i]]) -
                           dist(cities_coord[path[i]], cities_coord[path[next_i]]) -
                           dist(cities_coord[path[prev_j]], cities_coord[path[j]]) -
                           dist(cities_coord[path[j]], cities_coord[path[next_j]]);

        if (diff_dist < 0) swap(path[i], path[j]);
    }
    cout << "loop count: " << loop_count << endl;
}

