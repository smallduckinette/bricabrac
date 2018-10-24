CXX = g++
CXXFLAGS = -ggdb -O0 -std=c++17 -W -Wall -Werror -pedantic
LDFLAGS  = -fuse-ld=gold $(shell pkg-config sfml-graphics sfml-window sfml-system sfml-audio --libs) -pthread

# Main binary
TARGET      = bin/main.app
TARGET_SRCS = src/main.cpp
TARGET_OBJS = $(TARGET_SRCS:.cpp=.o)

# Unit-tests
UTEST      = bin/unittests.app
UTEST_SRCS = src/unittests.cpp src/test_gameplay.cpp src/test_physics.cpp
UTEST_OBJS = $(UTEST_SRCS:.cpp=.o)

# Library
LIB    = lib/libbab.a
SRCS   = src/collisiondata.cpp src/frame.cpp src/gameplay.cpp src/gamescreen.cpp src/graphicsubsystem.cpp src/guiscreen.cpp src/leveldescription.cpp src/lifes.cpp src/physics.cpp src/physicsubsystem.cpp src/powerbrick.cpp src/screen.cpp src/soundsubsystem.cpp src/titlescreen.cpp src/vector.cpp src/world.cpp
OBJS   = $(SRCS:.cpp=.o)

# Dependencies
DEPS   = $(SRCS:.cpp=.depends) $(TARGET_SRCS:.cpp=.depends) $(UTEST_SRCS:.cpp=.depends) 


.PHONY: clean all

all: $(LIB) $(TARGET) $(UTEST)

$(TARGET): $(LIB) $(TARGET_OBJS)
	$(CXX) $(CXXFLAGS) $(TARGET_OBJS) -o $(TARGET) -Llib -lbab $(LDFLAGS)

$(UTEST): $(LIB) $(UTEST_OBJS)
	$(CXX) $(CXXFLAGS) $(UTEST_OBJS) -o $(UTEST) -Llib -lbab $(LDFLAGS)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@

clean:
	rm -f $(TARGET) $(TARGET_OBJS) $(UTEST) $(UTEST_OBJS) $(LIB) $(OBJS) $(DEPS) 

-include $(DEPS)
