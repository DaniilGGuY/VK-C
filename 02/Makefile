CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = allocator_test
SRC = allocator_test.cpp allocator.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lgtest -lgtest_main -lpthread

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean