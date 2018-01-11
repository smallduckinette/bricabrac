CXX = g++
CXXFLAGS = -ggdb -O3 -std=c++11 -W -Wall -Werror -pedantic
LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -pthread

TARGET = main
SRCS   = brick.cpp main.cpp plateau.cpp physics.cpp
OBJS   = $(SRCS:.cpp=.o)
DEPS   = $(SRCS:.cpp=.depends)

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)
