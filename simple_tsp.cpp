/* * * *
 * Todo
 * [x] 2-opt
 * [] 3-opt (実装難しすぎ)
   [] n-opt (一般化できねぇ、実装つらい)
   [x] nearest neighbor algorithm
   [x] bitDP                         *
   [x] simulated annealing           *
   [x] optuna                        *
                               * * * */

/*
 * -- optunaについて
 * 焼き鈍しの温度関数に経過時間を使っている以上、乱数の初期化シードを固定しても出力結果は一定にならない。
 * optunaで最適化した際のminimum total distは17042.31804541591だが、そのパラメータで再度実行しても再現性はない
 * 誤差は数百くらいあるため、ぶっちゃけ1e4も回す必要はなかった。人間が適当に決めてもそれなりの値は出てたと思う。
 * best parameters:  {'temp radix': 233.55017584597834, 'probability coefficient': 9.710768225026422e-05}
 *
 * -- preprocessingとsimulated annealingについて
 * simulated annealingは局所解に陥らないように動くので、preprocessingはあまり意味をなさないかもしれない。
 *
 * -- bitDPについて
 * 書いて試したけど、高々数十程度の改善にしかならない。ただ、その程度ならば大体毎回改善している。
 *
 * -- 焼き鈍しのbest_nodesのメモについて
 * 焼き鈍しの思想としてはメモは不必要というか作らなくても良いようなパラメータを探せと言われてしまうかもしれないけど
 * メモした方が安定するからメモします。
 *
 * -- *processorについて
 * 雛形を作った方がいい気がする
 * */

// default                                     : 2.64764e+05
// simple_preprocessing                        : 1.56876e+05
// simple_solver                               : 4.15114e+04
// simple_solver + simple_preprocessing        : 3.63035e+04
// 2-opt                                       : 1.92137e+04
// 2-opt + simple_preprocessing                : 1.92300e+04
// simple_solver(1sec) + 2-opt(2sec) + sp      : 1.89941e+04
// simple_solver(1.5sec) + 2-opt(1.5sec) + sp  : 1.90244e+04
// simple_solver(2sec) + 2-opt(1sec) + sp      : 1.88177e+04
// -- upgrade simple_solver --
// simple_solver(2sec) + 2-opt(1sec) + sp      : 1.84935e+04
// simulated_annealing + 2-opt                 : 1.72736e+04
// -- tuning with optuna (5077th out of 1e4 times, about 8h20m) --
// simulated_annealing + 2-opt                 : 1.71558e+04
// only nearest_neighbor                       : 9.37335e+04


#include <bits/stdc++.h>
#include "random/xor_shift.h"
#include "utility/utilities.h"
#include "optimizers/optimizers.h"
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)

void initialize();
void finalize();

Vec2 cities_coord[CITY_NUM]={};
int path[CITY_NUM]={};

int main(int argc, char *argv[]) {
    stopwatch sw; sw.start();
    initialize();

    SimulatedAnnealing::Parameters params;
    params.ms_time_limit = 3000;
    params.TEMP_RADIX = 233;
    params.PROBABILITY_COEF = 9.71e-5;

    Preprocessors preprocessors = Preprocessors::nearest_neighbor_preprocess();
    Processors processors = Processors::SA_two_opt_process(params);
    Postprocessors postprocessors = Postprocessors::bitDP_postprocess(10, 1);

    bool do_log = true;
//    Optimizer optimizer(preprocessors, processors, postprocessors);
    Optimizer optimizer = Optimizer::default_optimizer();
    optimizer.optimize(path, do_log);

    finalize();
    sw.print_us();
    sw.print_ms();
    sw.print_sec();
}

void make_city() {
    rep(i,CITY_NUM) {
        int x = rand_range(MAX_COORD - MIN_COORD + 1) + MIN_COORD;
        int y = rand_range(MAX_COORD - MIN_COORD + 1) + MIN_COORD;
        cities_coord[i] = Vec2(x,y);
    }
}

void initialize() {
    init_rand_seed(112358);
    make_city();
    rep(i,CITY_NUM) path[i] = i;
}

void check() {
    int cnt[CITY_NUM]={};
    rep(i,CITY_NUM) cnt[path[i]]++;
    rep(i,CITY_NUM) if (cnt[i] != 1) {
        cerr << "cities are duplicated" << endl;
        exit(1);
    }
}

void finalize() {
    check();
    cout << "total dist: " << scientific << setprecision(5) << calc_total_dist(path) << endl;
}

