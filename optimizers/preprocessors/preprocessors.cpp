#include <iostream>
#include "preprocessors.h"
#include "nearest_neighbor/nearest_neighbor.h"
#include "sort/xy_sort/xy_sort.h"
#include "sort/yx_sort/yx_sort.h"

using namespace std;

Preprocessors::Preprocessors() : processes(std::vector<Parameters>()) {}
Preprocessors::Preprocessors(std::vector<Parameters> _processes) : processes(std::move(_processes)) {}

Preprocessors Preprocessors::operator+( const Preprocessors& another ) const {
    std::vector<Parameters> _processes;
    for(auto i : this->processes) _processes.push_back(i);
    for(auto i : another.processes) _processes.push_back(i);
    return Preprocessors(_processes);
}

Preprocessors Preprocessors::operator+=( const Preprocessors& another) {
    for(auto i : another.processes) processes.push_back(i);
    return *this;
}

Preprocessors Preprocessors::nearest_neighbor_preprocess() {
    return Preprocessors({Parameters(NEAREST_NEIGHBOR_MODE)});
}

Preprocessors Preprocessors::xy_sort_preprocess() {
    return Preprocessors({Parameters(XY_SORT_MODE)});
}

Preprocessors Preprocessors::yx_sort_preprocess() {
    return Preprocessors({Parameters(YX_SORT_MODE)});
}

void Preprocessors::preprocessing(int path[CITY_NUM], bool do_log) {
    if (do_log) cout << "preprocessing has started." << endl;
    for(auto i : processes) {
        if (i.mode == NEAREST_NEIGHBOR_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nnearest neighbor preprocess has started." << endl;
                cout << "    | now dist              : " << now_dist << endl;
            }
            nearest_neighbor(path);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after preprocess : " << dist_ap << endl;
                cout << "    | variation             : " << dist_ap - now_dist << endl;
                cout << "nearest neighbor preprocess has finished.\n" << endl;
            }
        }
        else if (i.mode == XY_SORT_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nxy sort preprocess has started." << endl;
                cout << "    | now dist              : " << now_dist << endl;
            }
            xy_sort(path);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after preprocess : " << dist_ap << endl;
                cout << "    | variation             : " << dist_ap - now_dist << endl;
                cout << "xy sort preprocess has finished.\n" << endl;
            }
        }
        else if (i.mode == YX_SORT_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nyx sort preprocess has started." << endl;
                cout << "    | now dist              : " << now_dist << endl;
            }
            yx_sort(path);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after preprocess : " << dist_ap << endl;
                cout << "    | variation             : " << dist_ap - now_dist << endl;
                cout << "yx sort preprocess has finished.\n" << endl;
            }
        }
    }
}
