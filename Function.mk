CXX = g++ -std=gnu++11
CXXFLAGS = -Wall -g -D FUNCTION_UNIT_TEST
INCLUDES = 
LIBS =
OBJS = Function.o
PROGRAM = Function.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
