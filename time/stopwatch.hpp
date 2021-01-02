#pragma once

#include <iostream>
#include <chrono>

class stopwatch {
    std::chrono::system_clock::time_point m_start;
public:

    stopwatch();

    void clear();
    bool is_started();
    void start();
    unsigned long get_sec();
    unsigned long get_ms();
    unsigned long get_us();
    void print_sec();
    void print_ms();
    void print_us();
};

inline stopwatch::stopwatch() : m_start(std::chrono::system_clock::time_point::min()) {}

inline void stopwatch::clear() {
    m_start = std::chrono::system_clock::time_point::min();
}

inline bool stopwatch::is_started() {
    return (m_start.time_since_epoch() != std::chrono::system_clock::time_point::min().time_since_epoch());
}

inline void stopwatch::start() {
    m_start = std::chrono::system_clock::now();
}

inline unsigned long stopwatch::get_sec() {
    if (is_started()) {
        std::chrono::system_clock::duration  diff;
        diff = std::chrono::system_clock::now() - m_start;
        return (unsigned)(std::chrono::duration_cast<std::chrono::seconds>(diff).count());
    }
    return 0;
}

inline unsigned long stopwatch::get_ms() {
    if (is_started()) {
        std::chrono::system_clock::duration  diff;
        diff = std::chrono::system_clock::now() - m_start;
        return (unsigned)(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
    }
    return 0;
}

inline unsigned long stopwatch::get_us() {
    if (is_started()) {
        std::chrono::system_clock::duration  diff;
        diff = std::chrono::system_clock::now() - m_start;
        return (unsigned)(std::chrono::duration_cast<std::chrono::microseconds>(diff).count());
    }
    return 0;
}

inline void stopwatch::print_sec() {
    printf("%lu [sec]\n", get_sec());
}

inline void stopwatch::print_ms() {
    printf("%lu [ms]\n", get_ms());
}

inline void stopwatch::print_us() {
    printf("%lu [us]\n", get_us());
}
