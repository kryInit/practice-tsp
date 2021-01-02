#include <iostream>
#include "utility/utilities.h"
#include "processors.h"
#include "2-opt/2-opt.h"
#include "random_swap/random_swap.h"
using namespace std;

Processors::Processors() : processes(std::vector<Parameters>()) {}
Processors::Processors(std::vector<Parameters> _processes) : processes(std::move(_processes)) {}

Processors Processors::operator+( const Processors& another ) const {
    std::vector<Parameters> _processes;
    for(auto i : this->processes) _processes.push_back(i);
    for(auto i : another.processes) _processes.push_back(i);
    return Processors(_processes);
}

Processors Processors::operator+=( const Processors& another) {
    for(auto i : another.processes) processes.push_back(i);
    return *this;
}

Processors Processors::two_opt_process(unsigned int ms_time_limit) {
    return Processors({Parameters(TWO_OPT_MODE, ms_time_limit)});
}

Processors Processors::random_swap_process(unsigned int ms_time_limit) {
    return Processors({Parameters(SWAP_MODE, ms_time_limit)});
}

Processors Processors::SA_two_opt_process(SAParams sa_params) {
    return Processors({Parameters(SA_2OPT_MODE, 0, sa_params)});
}

void Processors::processing(int path[CITY_NUM], bool do_log) {
    if (do_log) cout << "main processing has started." << endl;
    for(auto i : processes) {
        if (i.mode == TWO_OPT_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\n2-opt process has started." << endl;
                cout << "    | time limit         : " << i.ms_time_limit << "[ms]" << endl;
                cout << "    | now dist           : " << now_dist << endl;
            }
            two_opt(path, i.ms_time_limit);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after process : " << dist_ap << endl;
                cout << "    | variation          : " << dist_ap - now_dist << endl;
                cout << "2-opt process has finished.\n" << endl;
            }
        }
        else if (i.mode == SWAP_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nrandom swap process has started." << endl;
                cout << "    | time limit         : " << i.ms_time_limit << "[ms]" << endl;
                cout << "    | now dist           : " << now_dist << endl;
            }
            random_swap(path, i.ms_time_limit);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after process : " << dist_ap << endl;
                cout << "    | variation          : " << dist_ap - now_dist << endl;
                cout << "random swap process has finished.\n" << endl;
            }
        }
        else if (i.mode == SA_2OPT_MODE) {
            double now_dist;
            if (do_log) {
                now_dist = calc_total_dist(path);
                cout << "\nSA and 2-opt process has started." << endl;
                cout << "    | time limit         : " << i.sa_params.ms_time_limit << "[ms]" << endl;
                cout << "    | now dist           : " << now_dist << endl;
            }
            SA_TwoOpt(path, i.sa_params).simulate(path);
            if (do_log) {
                double dist_ap = calc_total_dist(path);
                cout << "    | dist after process : " << dist_ap << endl;
                cout << "    | variation          : " << dist_ap - now_dist << endl;
                cout << "SA and 2-opt process has finished.\n" << endl;
            }
        }
    }
}