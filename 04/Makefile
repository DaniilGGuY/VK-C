CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -g
TARGET = matrix_test
SRC = test.cpp matrix.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean