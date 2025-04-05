CC = gcc
CFLAGS = -Wall -Wextra -g -lm
INCLUDES = -I.

TARGETS = fib_prime fib_prime_parallel
SRCS = fib_prime.c fib_prime_parallel.c fib_prime_functions.c
OBJS = $(SRCS:.c=.o)

# Default rule: Compile both executables
all: $(TARGETS)

# Compile fib_prime
fib_prime: fib_prime.o fib_prime_functions.o
	$(CC) $(CFLAGS) -o fib_prime fib_prime.o fib_prime_functions.o

# Compile fib_prime_parallel
fib_prime_parallel: fib_prime_parallel.o fib_prime_functions.o
	$(CC) $(CFLAGS) -o fib_prime_parallel fib_prime_parallel.o fib_prime_functions.o

# Compile source files into object files
%.o: %.c fib_prime_functions.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and binaries
clean:
	rm -f $(TARGETS) $(OBJS)
