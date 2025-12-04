CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -g
TARGET = test_bst
SRC = test.cpp
HEADERS = binary_tree.h bst_iterator.h
IMPL = binary_tree.hpp bst_iterator.hpp

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS) $(IMPL)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean