CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -L. -lpqueue -Wl,-rpath=.
INCLUDES = -I.

TARGET = main
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link the executable with libpqueue
$(TARGET): $(OBJS) libpqueue.a
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: %.c pqueue.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and binary
clean:
	rm -f $(TARGET) $(OBJS)

# Clean everything including the compiled libraries
distclean: clean
	rm -f libpqueue.a libpqueue.so
