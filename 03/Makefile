CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -g
TARGET = token_parser
TEST_TARGET = token_parser_test
MAIN_SRC = main.cpp
PARSER_SRC = token_parser.cpp
TEST_SRC = test.cpp

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(PARSER_SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_SRC) $(PARSER_SRC)

$(TEST_TARGET): $(TEST_SRC) $(PARSER_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(PARSER_SRC) -lgtest -lgtest_main -lpthread

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test run clean