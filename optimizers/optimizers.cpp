#include <iostream>
#include "optimizers.h"
using namespace std;

Optimizer::Optimizer(Preprocessors prep, Processors p, Postprocessors postp) {
    processor = std::move(p);
    preprocessor = std::move(prep);
    postprocessor = std::move(postp);
}

Optimizer Optimizer::default_optimizer() {
    SimulatedAnnealing::Parameters params;
    params.ms_time_limit = 5000;
    params.TEMP_RADIX = 233;
    params.PROBABILITY_COEF = 9.71e-5;

    Preprocessors preprocessor = Preprocessors::nearest_neighbor_preprocess();
    Processors processor = Processors::SA_two_opt_process(params);
    Postprocessors postprocessor = Postprocessors::bitDP_postprocess(8, 1);

    return {preprocessor, processor, postprocessor};
}

void Optimizer::optimize(int path[CITY_NUM], bool do_log) {
    cout << "\noptimization has started." << endl;
    preprocessor.preprocessing(path, do_log);
    processor.processing(path, do_log);
    postprocessor.postprocessing(path, do_log);
    cout << "optimization has finished.\n" << endl;
}
