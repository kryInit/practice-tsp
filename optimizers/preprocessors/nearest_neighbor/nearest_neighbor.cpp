#include <list>
#include <climits>
#include "nearest_neighbor.h"

using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

void nearest_neighbor(int path[CITY_NUM]) {
    list<int> l;
    rep(i,CITY_NUM) {
        if (i == 0) {
            l.insert(l.begin(), 0);
            continue;
        }
        auto now = l.begin();
        auto best_itr = l.begin();
        int min_diff_dist = INT_MAX;
        while(true) {
            int prev, next;
            prev = *now; ++now;
            next = (now == l.end() ? l.front() : *now);

            const int tmp_diff_dist = dist(cities_coord[prev], cities_coord[i]) +
                                      dist(cities_coord[i], cities_coord[next]) -
                                      dist(cities_coord[prev], cities_coord[next]);

            if (min_diff_dist > tmp_diff_dist) {
                min_diff_dist = tmp_diff_dist;
                best_itr = now;
                best_itr--;
            }

            if (now == l.end()) break;
        }
        l.insert(best_itr, i);
    }
    int cnt = 0;
    for(auto i : l) path[cnt++] = i;
}

