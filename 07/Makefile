CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g
TARGET = format_test
SRC = test.cpp

all: $(TARGET)

$(TARGET): $(SRC) format.h format.hpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean