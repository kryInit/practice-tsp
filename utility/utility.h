#ifndef TSP_UTILITY_H
#define TSP_UTILITY_H

const int CITY_NUM = 500;
const int MIN_COORD = -500;
const int MAX_COORD = 500;

struct Vec2 {
    int x, y;
    Vec2() : x(0.), y(0.) {};
    Vec2(int _x, int _y) {x = _x, y = _y; }
};

int square_dist(Vec2 a, Vec2 b);
double dist(Vec2 a, Vec2 b);
double calc_total_dist(int path[CITY_NUM]);


#endif
