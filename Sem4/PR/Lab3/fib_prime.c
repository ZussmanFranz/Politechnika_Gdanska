#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "fib_prime_functions.h"

int main() {
    clock_t start_time = clock();

    int count = count_fibonacci_primes(1, 1000000000);

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Total Fibonacci primes found: %d\n", count);
    printf("Execution time: %.2f seconds\n", elapsed_time);
    
    return 0;
}
