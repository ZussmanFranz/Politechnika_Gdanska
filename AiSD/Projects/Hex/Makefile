# Define the compiler
CC = /usr/bin/g++

# Define compiler flags
CFLAGS = -fdiagnostics-color=always -ggdb -pedantic-errors -Wall -Weffc++ -Wconversion -Wsign-conversion -Wextra -Wpedantic -g -lncurses -I $(INCDIR)

# Define the output executable name
OUTPUT = main

# Define directories
SRCDIR = src
OBJDIR = build/obj
BINDIR = build/bin
INCDIR = $(SRCDIR)/include

# Ensure the build directories exist
MKDIR_P = mkdir -p

# Define the source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Define the object files
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Define the default target
all: directories $(BINDIR)/$(OUTPUT)

# Link all object files into a single executable
$(BINDIR)/$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

# Compile each .cpp file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure necessary directories exist
directories: $(OBJDIR) $(BINDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

$(BINDIR):
	$(MKDIR_P) $(BINDIR)

# Define the clean target
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(OUTPUT)