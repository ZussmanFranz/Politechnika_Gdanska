#include <stdbool.h>

// Function to check if a number is prime
bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

// Function to check if a number is in the Fibonacci sequence
bool is_fibonacci(int x) {
    if (x == 0 || x == 1) return true;
    int a = 0, b = 1, temp;
    while (b < x) {
        temp = b;
        b = a + b;
        a = temp;
    }
    return (b == x);
}

// Function to count Fibonacci primes in a given range
int count_fibonacci_primes(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (is_fibonacci(i) && is_prime(i)) {
            count++;
        }
    }
    return count;
}