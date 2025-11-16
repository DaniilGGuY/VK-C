CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g
TARGET = vector_test
SRC = test.cpp

all: $(TARGET)

$(TARGET): $(SRC) Vector.h Vector.hpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean