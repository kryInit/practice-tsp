#pragma once

#include <iostream>
#include "stopwatch.hpp"

class time_manager : public stopwatch {
    unsigned long ms_time_limit;
public:
    explicit time_manager(unsigned long _ms_time_limit);
    bool is_within_time_limit();
};

inline time_manager::time_manager(unsigned long _ms_time_limit) : ms_time_limit(_ms_time_limit) {
    start();
}

inline bool time_manager::is_within_time_limit() {
    return get_ms() < ms_time_limit;
}
