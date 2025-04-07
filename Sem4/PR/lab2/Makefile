# Makefile for building a shared library and a dynamic executable

# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC
OPTFLAGS = -O3 -ffast-math
LDFLAGS = -lm
TARGET = program_dynamic
LIB_NAME = lib_invsqrts.so

# Source files
MAIN_SRC = main.c
OPT_SRC = opt_invsqrt.c
BASIC_SRC = invsqrt.c

# Object files
MAIN_OBJ = main.o
OPT_OBJ = opt_invsqrt.o
BASIC_OBJ = invsqrt.o

# Default rule
all: $(TARGET)

# Compile optimized inverse sqrt
$(OPT_OBJ): $(OPT_SRC)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@ $(LDFLAGS)

# Compile basic inverse sqrt
$(BASIC_OBJ): $(BASIC_SRC)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# Build the shared library
$(LIB_NAME): $(OPT_OBJ) $(BASIC_OBJ)
	$(CC) $(OPT_OBJ) $(BASIC_OBJ) -shared -o $@

# Compile main
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) -c $(MAIN_SRC) -o $(MAIN_OBJ) -I ./

# Link everything into the final program
$(TARGET): $(MAIN_OBJ) $(LIB_NAME)
	$(CC) $(MAIN_OBJ) -L. -l:$(LIB_NAME) $(LDFLAGS) -o $(TARGET)

# Run the program with LD_LIBRARY_PATH
run: $(TARGET)
	LD_LIBRARY_PATH=. ./$(TARGET)

# Clean rule
clean:
	rm -f *.o $(LIB_NAME) $(TARGET)

.PHONY: all clean run
