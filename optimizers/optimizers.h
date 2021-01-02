#pragma once

#include "utility/utilities.h"
#include "processors/processors.h"
#include "preprocessors/preprocessors.h"
#include "postprocessors/postprocessors.h"


class Optimizer {
    Processors processor;
    Preprocessors preprocessor;
    Postprocessors postprocessor;

public:
    Optimizer() = default;

    Optimizer(Preprocessors prep, Processors p, Postprocessors postp);

    static Optimizer default_optimizer();

    void optimize(int path[CITY_NUM], bool do_log);
};


