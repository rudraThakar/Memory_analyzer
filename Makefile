CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -pthread

SRCS = main.cpp analyzer.cpp proc_utils.cpp formatter.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = proc_memscan

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean