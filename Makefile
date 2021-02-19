CXX = g++
CFLAGS = -c -Wall -pedantic
PROGRAM = Simulation
OBJS = Simulation.o Facility.o Picture.o

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) -o $(PROGRAM)

$(PROGRAM).o: $(PROGRAM).cpp
	$(CXX) $< $(CFLAGS) -o $@

%.o: %.cpp %.hpp
	$(CXX) $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJS) $(PROGRAM)
