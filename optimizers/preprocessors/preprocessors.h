#pragma once

#include <vector>
#include "nearest_neighbor/nearest_neighbor.h"
#include "sort/xy_sort/xy_sort.h"
#include "sort/yx_sort/yx_sort.h"

class Preprocessors {
    static constexpr unsigned int NONE_MODE = -1;
    static constexpr unsigned int NEAREST_NEIGHBOR_MODE = 0;
    static constexpr unsigned int XY_SORT_MODE = 1;
    static constexpr unsigned int YX_SORT_MODE = 2;

    struct Parameters {
        unsigned int mode;

        Parameters() : mode(NONE_MODE) {}
        Parameters(unsigned int _mode) : mode(_mode) {}
    };

    std::vector<Parameters> processes;

public:
    Preprocessors();
    explicit Preprocessors(std::vector<Parameters> _processes);

    Preprocessors operator+( const Preprocessors& another ) const;

    Preprocessors operator+=( const Preprocessors& another);

    static Preprocessors nearest_neighbor_preprocess();

    static Preprocessors xy_sort_preprocess();

    static Preprocessors yx_sort_preprocess();

    void preprocessing(int path[CITY_NUM], bool do_log);
};
