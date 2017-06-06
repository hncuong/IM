CC=g++
CFLAGS=-c -O3 -Wall -std=c++0x
DEPS = limit.h

all: imrank

imrank: new_main.o IMRank.o graph.o heap.o general_cascade.o
	$(CC) -O3 new_main.o IMRank.o graph.o heap.o general_cascade.o -o imrank

new_main.o: new_main.cpp
	$(CC) $(CFLAGS) new_main.cpp	

IMRank.o: IMRank.cpp $(DEPS)
	$(CC) $(CFLAGS) IMRank.cpp

graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp 

heap.o: heap.cpp
	$(CC) $(CFLAGS) heap.cpp

general_cascade.o: general_cascade.cpp
	$(CC) $(CFLAGS) general_cascade.cpp

clean:
	rm -f *.o *~