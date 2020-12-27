#ifndef NDEBUG
#include <iostream>
#endif

using uint = unsigned int;

uint seed[4] = {1,2,3,4};

void init_rand_seed(uint s) {
    const uint magic_number = 1812433253;
    for(int i=1; i<=4; i++){
        seed[i-1] = s = magic_number * (s^(s>>30)) + (uint)i;
    }
}
uint rand_uint() {
    uint t = (seed[0]^(seed[0]<<11));
    seed[0]=seed[1];
    seed[1]=seed[2];
    seed[2]=seed[3];
    return seed[3]=(seed[3]^(seed[3]>>19))^(t^(t>>8));
}
uint rand_range(uint r) {
#ifndef NDEBUG
    if (r == 0) {
        std::cerr << "0 passed to rand_range(uint r)" << std::endl;
        exit(1);
    }
#endif
    return rand_uint()%r;
}

uint rand_range(uint l, uint r) {
#ifndef NDEBUG
    if (l >= r) {
        std::cerr << "l larger than r was passed to rand_range(uint l, uint r)" << std::endl;
        exit(1);
    }
#endif
    return rand_uint() % (r-l) + l;
}


