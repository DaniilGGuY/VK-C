CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: $(TARGET)
	./$(TARGET)

run: $(TARGET)
	@echo "Введите слова для сравнения:"
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: 
	all 
	test 
	run 
	clean