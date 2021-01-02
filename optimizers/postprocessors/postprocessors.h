#pragma once

#include <vector>
#include "bitDP/bitDP.h"

class Postprocessors {
    static constexpr unsigned int NONE_MODE = -1;
    static constexpr unsigned int BITDP_MODE = 0;

    struct Parameters {
        unsigned int mode;
        unsigned int size;
        unsigned int offset;

        Parameters() : mode(NONE_MODE), size(0), offset(0) {}
        explicit Parameters(unsigned int _mode) : mode(_mode), size(0), offset(0) {}
        Parameters(unsigned int _mode, unsigned int _size, unsigned int _offset) : mode(_mode), size(_size), offset(_offset) {}
    };

    std::vector<Parameters> processes;

public:
    Postprocessors();
    explicit Postprocessors(std::vector<Parameters> _processes);

    Postprocessors operator+( const Postprocessors& another ) const;

    Postprocessors operator+=( const Postprocessors& another);

    static Postprocessors bitDP_postprocess(unsigned int size, unsigned int offset);

    void postprocessing(int path[CITY_NUM], bool do_log);
};

