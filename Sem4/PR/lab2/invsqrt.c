#include <math.h>
#include <stdint.h>

// Default implementation of inverted square root using math function:
float normal_invsqrt(float number){
    return (1 / sqrtf(number));
}

// "Fast inverse square root" implementation
float fast_invsqrt(float number){
    union {
        float    f;
        uint32_t i;
    } conv = { .f = number };

    conv.i  = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    
    return conv.f;
}