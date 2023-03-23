CXX = g++
CXXFLAGS = -Wall -std=c++11
SRCS = main.cpp TSP.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = tsp

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(MAIN)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN)
