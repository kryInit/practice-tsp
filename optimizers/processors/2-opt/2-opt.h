#pragma once

#include "utility/utilities.h"

class TwoOpt {
protected:
    Node nodes[CITY_NUM];
    int calc_diff_sdist(unsigned int a, unsigned int c);
    void update_nodes(unsigned int a, unsigned int c);

public:
    explicit TwoOpt(int path[CITY_NUM]);
    void two_opt();
    void overwrite_path(int path[CITY_NUM]);
};

void two_opt(int path[CITY_NUM], unsigned int ms_time_limit);
