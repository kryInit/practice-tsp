#pragma once

#include <vector>
#include "simulated_annealing/sa_and_2-opt.h"

class Processors {
    static constexpr unsigned int NONE_MODE = -1;
    static constexpr unsigned int TWO_OPT_MODE = 0;
    static constexpr unsigned int SWAP_MODE = 1;
    static constexpr unsigned int SA_2OPT_MODE = 2;

    using SAParams = SimulatedAnnealing::Parameters;
    struct Parameters {
        unsigned int mode;
        unsigned int ms_time_limit;
        SAParams sa_params;

        Parameters() : mode(NONE_MODE), ms_time_limit(0), sa_params(SAParams()) {}
        Parameters(unsigned int _mode, unsigned int _ms_time_limit) : mode(_mode), ms_time_limit(_ms_time_limit), sa_params(SAParams()) {}
        Parameters(unsigned int _mode, unsigned int _ms_time_limit, SAParams _sa_params) : mode(_mode), ms_time_limit(_ms_time_limit),  sa_params(_sa_params) {}
    };

    std::vector<Parameters> processes;

public:
    Processors();
    explicit Processors(std::vector<Parameters> _processes);

    Processors operator+( const Processors& another ) const;

    Processors operator+=( const Processors& another);

    static Processors two_opt_process(unsigned int ms_time_limit);

    static Processors random_swap_process(unsigned int ms_time_limit);

    static Processors SA_two_opt_process(SAParams sa_params);

    void processing(int path[CITY_NUM], bool do_log);
};