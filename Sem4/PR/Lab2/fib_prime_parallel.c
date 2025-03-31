#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "fib_prime_functions.h"

#define RANGE_START 1
#define RANGE_END 1000000000
#define NUM_PROCESSES 7

// Function to fork a child process and wait for its result
int fork_child(int start, int end) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process: count Fibonacci primes and exit with result
        int result = count_fibonacci_primes(start, end);
        exit(result);
    } else {
        // Parent process: wait for child and return its result
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int main() {
    clock_t start_time = clock();

    int range_size = (RANGE_END - RANGE_START + 1) / NUM_PROCESSES;
    int total_count = 0;

    printf("Root process (PID: %d) started.\n", getpid());

    // Root process spawns child_1 and child_2
    int child_1_count = 0, child_2_count = 0;

    pid_t child_1 = fork();
    if (child_1 == 0) {
        // Child 1 spawns leaf_1_1 and leaf_1_2
        int leaf_1_1_count = fork_child(RANGE_START, RANGE_START + range_size - 1);
        int leaf_1_2_count = fork_child(RANGE_START + range_size, RANGE_START + 2 * range_size - 1);

        // Child 1 also computes its own range
        int child_1_self_count = count_fibonacci_primes(RANGE_START + 2 * range_size, RANGE_START + 3 * range_size - 1);
        
        int child_1_total = leaf_1_1_count + leaf_1_2_count + child_1_self_count;
        exit(child_1_total);
    }

    pid_t child_2 = fork();
    if (child_2 == 0) {
        // Child 2 spawns leaf_2_1 and leaf_2_2
        int leaf_2_1_count = fork_child(RANGE_START + 4 * range_size, RANGE_START + 5 * range_size - 1);
        int leaf_2_2_count = fork_child(RANGE_START + 5 * range_size, RANGE_START + 6 * range_size - 1);

        // Child 2 also computes its own range
        int child_2_self_count = count_fibonacci_primes(RANGE_START + 6 * range_size, RANGE_END);

        int child_2_total = leaf_2_1_count + leaf_2_2_count + child_2_self_count;
        exit(child_2_total);
    }

    // Root also computes its own range
    int root_self_count = count_fibonacci_primes(RANGE_START + 3 * range_size, RANGE_START + 4 * range_size - 1);

    // Gather results from child_1 and child_2
    int status;
    waitpid(child_1, &status, 0);
    child_1_count = WEXITSTATUS(status);

    waitpid(child_2, &status, 0);
    child_2_count = WEXITSTATUS(status);

    total_count = root_self_count + child_1_count + child_2_count;

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Total Fibonacci primes found: %d\n", total_count);
    printf("Execution time: %.2f seconds\n", elapsed_time);

    return 0;
}
