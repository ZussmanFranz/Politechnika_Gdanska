# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -O2

# Target executable name
TARGET  = main

# Source files
SRCS    = main.c priority_queue_list.c

# Object files derived from source files
OBJS    = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking: create the executable from object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation: compile each .c file to a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
