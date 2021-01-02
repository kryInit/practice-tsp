#include <bits/stdc++.h>
#include "bitDP.h"

using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)
#define mp make_pair

extern Vec2 cities_coord[CITY_NUM];

void bitDP(int path[CITY_NUM], const unsigned int size, const unsigned int offset) {
    using uint = unsigned int;
    const int N = (1<<size);
    int path_memo[CITY_NUM] = {};
    for(int th=0; th < CITY_NUM; th += offset) {
        const int s = (th-1+CITY_NUM)%CITY_NUM;
        const int t = (th+size)%CITY_NUM;

        vector<vector<pair<uint,vector<int>>>> dp(size,vector<pair<uint,vector<int>>>(N, make_pair(INT_MAX,vector<int>())));
        rep(i,size) {
            int I = (i+th)%CITY_NUM;
            vector<int> tmp(1); tmp[0] = I;
            dp[i][(1<<i)] = mp(square_dist(cities_coord[path[s]], cities_coord[path[I]]), tmp);
        }
        rep(i,N) rep(j,size) if (i&(1<<j)) rep(k,size) if (!(i&(1<<k))) {
            int J = (j+th)%CITY_NUM, K = (k+th)%CITY_NUM;
            uint tmp_dist = dp[j][i].first + square_dist(cities_coord[path[J]], cities_coord[path[K]]);
            if (dp[k][i|(1<<k)].first > tmp_dist) {
                dp[k][i|(1<<k)] = dp[j][i];
                dp[k][i|(1<<k)].first = tmp_dist;
                dp[k][i|(1<<k)].second.push_back(K);
            }
        }

        int best_idx = 0;
        uint min_total_dist = UINT_MAX;
        rep(i,size) {
            int I = (i+th)%CITY_NUM;
            uint tmp_total_dist = dp[i][N-1].first + square_dist(cities_coord[path[I]], cities_coord[path[t]]);
            if (min_total_dist > tmp_total_dist) {
                min_total_dist = tmp_total_dist;
                best_idx = i;
            }
        }
        rep(i,size) {
            int I = (i+th)%CITY_NUM;
            path_memo[I] = path[I];
        }
        rep(i,size) {
            int I = (i+th)%CITY_NUM;
            path[I] = path_memo[dp[best_idx][N-1].second[i]];
        }
    }
}
