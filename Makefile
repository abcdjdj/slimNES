SOURCES = cpu.cpp main.cpp memory.cpp
INCLUDES = include/

# Target
TARGET = cpu

CXX = g++
LD = ld
CXXFLAGS = -Wall -Werror -O0

OBJS = $(SOURCES:.cpp=.o)

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -I$(INCLUDES) -o $@.out

%.o : %.cpp
	$(CXX) $< -c $(CXXFLAGS) $(LDFLAGS) -I$(INCLUDES) -o $@

.PHONY: clean
clean :
	rm -rf *.o *.out
