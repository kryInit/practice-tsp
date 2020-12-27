#include "nodes.h"
#include "../../random/xor_shift.h"

using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

int TwoOpt::calc_diff_sdist(const unsigned int a, const unsigned int c) {
    const unsigned int b = nodes[a].next, d = nodes[c].next;
    if (b == c || d == a) return 0;
    return (int)(square_dist(cities_coord[a], cities_coord[c]) + square_dist(cities_coord[b], cities_coord[d]))
         - (int)(square_dist(cities_coord[a], cities_coord[b]) + square_dist(cities_coord[c], cities_coord[d]));
}

void TwoOpt::update_nodes(const unsigned int a, const unsigned int c) {
    const unsigned int b = nodes[a].next, d = nodes[c].next;
    unsigned int now = c;
    while(now != a) {
        swap(nodes[now].prev, nodes[now].next);
        now = nodes[now].next;
    }
    nodes[a].next = c;
    nodes[c].prev = a;
    nodes[b].next = d;
    nodes[d].prev = b;
}

TwoOpt::TwoOpt(int path[CITY_NUM]) {
    rep(i,CITY_NUM) {
        if (i && i < CITY_NUM-1) {
            nodes[path[i]].next = path[i+1];
            nodes[path[i]].prev = path[i-1];
        } else if (!i) {
            nodes[path[i]].next = path[i+1];
            nodes[path[i]].prev = path[CITY_NUM-1];
        } else {
            nodes[path[i]].next = path[0];
            nodes[path[i]].prev = path[i-1];
        }
    }
}

void TwoOpt::two_opt() {

    /* * * * * * * * * *
     * a → b     a → c *
     * ↑   ↓  →  ↑   ↓ *
     * d ← c     d ← b *
     * * * * * * * * * */

    unsigned int a = rand_range(CITY_NUM), c = rand_range(CITY_NUM);
    while(a == c) { c = rand_range(CITY_NUM); }
    if (calc_diff_sdist(a, c) < 0) {
        update_nodes(a, c);
    }
}

void TwoOpt::overwrite_path(int path[CITY_NUM]) {
    int i = 0;
    int now = 0;
    rep(_,CITY_NUM) {
        path[i++] = now;
        now = nodes[now].next;
    }
}
