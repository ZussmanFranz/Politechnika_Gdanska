CC = g++
CFLAGS = -I src/include

SRC_DIR = src
INCLUDE_DIR = $(SRC_DIR)/include

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(INCLUDE_DIR)/*.cpp)

OBJS = $(SRC_FILES:.cpp=.o)

TARGET = project

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJS)
