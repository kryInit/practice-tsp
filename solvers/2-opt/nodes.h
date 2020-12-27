#ifndef NODES_H
#define NODES_H

#include "../../utility/utilities.h"

struct Node {
    int prev, next;
    Node() : prev(0), next(0) {}
    Node(int _prev, int _next) { prev = _prev; next = _next; }
};

class TwoOpt {
    Node nodes[CITY_NUM];
    int calc_diff_sdist(unsigned int a, unsigned int c);
    void update_nodes(unsigned int a, unsigned int c);

public:
    explicit TwoOpt(int path[CITY_NUM]);
    void two_opt();
    void overwrite_path(int path[CITY_NUM]);
};

#endif
