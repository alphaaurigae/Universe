CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O3 -pthread
LDFLAGS := -pthread

PROGRAM := universe

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(PROGRAM) $(OBJS)