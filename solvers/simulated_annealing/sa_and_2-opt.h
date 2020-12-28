#ifndef SA_AND_2_OPT_H
#define SA_AND_2_OPT_H

#include <iostream>
#include "../../utility/utilities.h"
#include "../2-opt/2-opt.h"
#include "simulated_annealing_template.h"

class SA_TwoOpt : private SimulatedAnnealing, private TwoOpt {
public:
    SA_TwoOpt(int path[CITY_NUM], ParametersForSA params)
        : SimulatedAnnealing(params)
        , TwoOpt(path) {}

    void simulate(int path[CITY_NUM]) {
        int loop_count = 0;
        int min_diff_sdist = 0;
        int now_diff_sdist = 0;
        Node best_nodes[CITY_NUM];
        while(permit_continuation()) {
            loop_count++;
            unsigned int a = rand_range(CITY_NUM), c = rand_range(CITY_NUM);
            while(a == c) { c = rand_range(CITY_NUM); }
            int diff_sdist = calc_diff_sdist(a, c);
            if (permit_transition(diff_sdist)) {
                update_nodes(a, c);
                now_diff_sdist += diff_sdist;
                if (min_diff_sdist > now_diff_sdist) {
                    min_diff_sdist = now_diff_sdist;
                    for(int i=0; i<CITY_NUM; ++i) best_nodes[i] = nodes[i];
                }
            }
        }
        std::cout << "loop count: " << loop_count << std::endl;
        for(int i=0; i<CITY_NUM; ++i) nodes[i] = best_nodes[i];
        overwrite_path(path);
    }
};


#endif
