CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g
TARGET = bigint_test
SRC = test.cpp BigInt.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean