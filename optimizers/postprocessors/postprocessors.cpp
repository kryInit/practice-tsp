#include <iostream>
#include "postprocessors.h"
using namespace std;


Postprocessors::Postprocessors() : processes(std::vector<Parameters>()) {}
Postprocessors::Postprocessors(std::vector<Parameters> _processes) : processes(std::move(_processes)) {}

Postprocessors Postprocessors::operator+( const Postprocessors& another ) const {
    std::vector<Parameters> _processes;
    for(auto i : this->processes) _processes.push_back(i);
    for(auto i : another.processes) _processes.push_back(i);
    return Postprocessors(_processes);
}

Postprocessors Postprocessors::operator+=( const Postprocessors& another) {
    for(auto i : another.processes) processes.push_back(i);
    return *this;
}

Postprocessors Postprocessors::bitDP_postprocess(unsigned int size, unsigned int offset) {
    return Postprocessors({Parameters(BITDP_MODE, size, offset)});
}

void Postprocessors::postprocessing(int path[CITY_NUM], bool do_log) {
    if (do_log) cout << "postprocessing has started." << endl;
    for(auto i : processes) {
        if (i.mode == BITDP_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nbitDP postprocess has started." << endl;
                cout << "    | now dist               : " << now_dist << endl;
            }
            bitDP(path, i.size, i.offset);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after postprocess : " << dist_ap << endl;
                cout << "    | variation              : " << dist_ap - now_dist << endl;
                cout << "bitDP postprocess has finished.\n" << endl;
            }
        }
    }
}

