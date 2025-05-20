CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

main: cpp/main.cpp cpp/database.cpp
	$(CXX) $(CXXFLAGS) -o main cpp/main.cpp cpp/database.cpp

clean:
	rm -f main

test: cpp/tests/test_database.cpp cpp/database.cpp
	$(CXX) $(CXXFLAGS) -o test cpp/tests/test_database.cpp cpp/database.cpp
benchmark:
	$(CXX) $(CXXFLAGS) -o benchmark benchmarks/benchmark_insert.cpp cpp/database.cpp
