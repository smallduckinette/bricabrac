CXX = g++
CXXFLAGS = -ggdb -O3 -std=c++11 -W -Wall -Werror -pedantic
LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -pthread

# Main binary
TARGET      = main.app
TARGET_SRCS = main.cpp
TARGET_OBJS = $(TARGET_SRCS:.cpp=.o)

# Unit-tests
UTEST      = unittests.app
UTEST_SRCS = unittests.cpp test_physics.cpp
UTEST_OBJS = $(UTEST_SRCS:.cpp=.o)

# Library
LIB    = libbab.a
SRCS   = ball.cpp brick.cpp plateau.cpp physics.cpp
OBJS   = $(SRCS:.cpp=.o)

# Dependencies
DEPS   = $(SRCS:.cpp=.depends) $(TARGET_SRCS:.cpp=.depends) 


.PHONY: clean all

all: $(LIB) $(TARGET) $(UTEST)

$(TARGET): $(LIB) $(TARGET_OBJS)
	$(CXX) $(CXXFLAGS) $(TARGET_OBJS) -o $(TARGET) -L. -lbab $(LDFLAGS)

$(UTEST): $(LIB) $(UTEST_OBJS)
	$(CXX) $(CXXFLAGS) $(UTEST_OBJS) -o $(UTEST) -L. -lbab $(LDFLAGS)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@

clean:
	rm -f $(TARGET) $(TARGET_OBJS) $(UTEST) $(UTEST_OBJS) $(LIB) $(OBJS) $(DEPS) 

-include $(DEPS)
