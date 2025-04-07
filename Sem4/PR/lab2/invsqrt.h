#ifndef _INVSQRT_H_
#define _INVSQRT_H

#include <math.h>
#include <stdint.h>

// Default implementation of inverted square root using math function:
float normal_invsqrt(float number);

// "Fast inverse square root" implementation
float fast_invsqrt(float number);

#endif