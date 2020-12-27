#ifndef TSP_UTILITY_H
#define TSP_UTILITY_H

#include "Vec2.h"
#include "constant.h"

unsigned int square_dist(Vec2 a, Vec2 b);
double dist(Vec2 a, Vec2 b);
double calc_total_dist(int path[CITY_NUM]);


#endif
