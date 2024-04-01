SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: main

main: $(OBJ_FILES)
	g++ -I src/include -o $@ $^

%.o: %.cpp
	g++ -I src/include -c -o $@ $<

clean:
	rm -f main $(OBJ_FILES)
