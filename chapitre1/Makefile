CXX = g++
CXXFLAGS = -ggdb -O3 -std=c++17 -W -Wall -Werror -ansi -pedantic
LDFLAGS  = -fuse-ld=gold -lsfml-graphics -lsfml-window -lsfml-system -pthread

TARGET = main.app
SRCS   = main.cpp
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
