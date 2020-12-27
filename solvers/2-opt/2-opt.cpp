#include "../../time/time_manager.hpp"
#include "2-opt.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

extern Vec2 cities_coord[CITY_NUM];

void simple_solver_using_2_opt(int path[CITY_NUM], const unsigned int ms_time_limit) {
    time_manager tm(ms_time_limit);
    TwoOpt two_opt(path);
    int loop_count = 0;
    while(tm.is_within_time_limit()) {
        loop_count++;
        two_opt.two_opt();
    }
    cout << "loop count: " << loop_count << endl;
    two_opt.overwrite_path(path);
}

