#include <math.h>
#include <stdio.h>

float normal_invsqrt(double number){
    return (1 / sqrt(number));
}

int main(){
    printf("1 / sqrt(25) = %f\n", normal_invsqrt(25));

    return 0;
}