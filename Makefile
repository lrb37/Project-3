CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

all: tsp

tsp: main.o tsp.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp tsp.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tsp.o: tsp.cpp tsp.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o tsp
