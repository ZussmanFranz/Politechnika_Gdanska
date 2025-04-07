#include <stdio.h>
#include <time.h>

#include <invsqrt.h>
#include <opt_invsqrt.h>

#define benchmark_number 12345678
#define benchmark_count 1000000000

int main(){
    clock_t start_time = clock();

    // repeat operation benchmark_count times
    for (int i = 0; i < benchmark_count; i++){
        fast_invsqrt(benchmark_number);
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Fast algorithm (result = %f) execution time: %.2f seconds\n", fast_invsqrt(benchmark_number), elapsed_time);


    start_time = clock();

    // repeat operation benchmark_count times
    for (int j = 0; j < benchmark_count; j++){
        opt_invsqrt(benchmark_number);
    }

    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Optimized algorithm (result = %f) execution time: %.2f seconds\n", opt_invsqrt(benchmark_number), elapsed_time);

    return 0;
}