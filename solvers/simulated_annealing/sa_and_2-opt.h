#ifndef SA_AND_2_OPT_H
#define SA_AND_2_OPT_H

#include <iostream>
#include "../../utility/utilities.h"
#include "../2-opt/2-opt.h"
#include "simulated_annealing_template.h"

class SA_TwoOpt : public SimulatedAnnealing, public TwoOpt {
public:
    SA_TwoOpt(int path[CITY_NUM], ParametersForSA params)
        : SimulatedAnnealing(params)
        , TwoOpt(path) {}

    void simulate(int path[CITY_NUM]) {
        int loop_count = 0;
        while(tm.is_within_time_limit()) {
            loop_count++;
            unsigned int a = rand_range(CITY_NUM), c = rand_range(CITY_NUM);
            while(a == c) { c = rand_range(CITY_NUM); }
            double diff_sdist = calc_diff_sdist(a, c);
            if (permit_transition(diff_sdist)) {
                update_nodes(a, c);
            }
        }
        std::cout << "loop count: " << loop_count << std::endl;
        overwrite_path(path);
    }
};


#endif
