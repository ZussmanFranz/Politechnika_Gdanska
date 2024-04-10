SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o) #add here the ncurses library 

all: main

main: $(OBJ_FILES)
	g++ -I src/include -o $@ $^ -lncurses

%.o: %.cpp
	g++ -I src/include -c -o $@ $< -lncurses

clean:
	rm -f main $(OBJ_FILES)
