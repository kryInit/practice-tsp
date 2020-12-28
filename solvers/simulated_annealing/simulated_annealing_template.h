#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "../../time/time_manager.hpp"
#include "../../random/xor_shift.h"
#include <cmath>
#include <climits>

struct ParametersForSA {
    unsigned int ms_time_limit;
    unsigned int TEMP_RADIX;
    double PROBABILITY_COEF;

    ParametersForSA() : ms_time_limit(0), TEMP_RADIX(1), PROBABILITY_COEF(1) {}
};

class SimulatedAnnealing {
protected:
    const unsigned int ms_time_limit;
    const unsigned int TEMP_RADIX;
    const double PROBABILITY_COEF;
    time_manager tm;
    double tempreture();
    double probability(double diff, double t);
    bool permit_transition(double diff);

public:
    explicit SimulatedAnnealing(ParametersForSA params)
        : ms_time_limit(params.ms_time_limit)
        , TEMP_RADIX(params.TEMP_RADIX)
        , PROBABILITY_COEF(params.PROBABILITY_COEF)
        , tm(params.ms_time_limit) {}
};

inline double SimulatedAnnealing::tempreture() {
    return pow((double)TEMP_RADIX, (double)tm.get_ms() / (double)ms_time_limit);
}

inline double SimulatedAnnealing::probability(double diff, double t) {
    if (diff < 0) return 1;
    else return exp(-diff*t*PROBABILITY_COEF);
}

inline bool SimulatedAnnealing::permit_transition(double diff) {
    return probability(diff, tempreture()) > ((double)rand_uint() / (double)UINT_MAX);
}

#endif
