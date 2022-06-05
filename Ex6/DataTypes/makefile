CC = g++ -std=c++17
STATIC = ar -rcs
LIB = -pthread
FLAGS = -g -Wall -fPIC


all: structures

# using alias so it knows not to recompile
structures: structures.so

# Shared library
structures.so: guard.o singleton.o queue.o activeObject.o tcpServer.o reactor.o
	$(CC) $(FLAGS) -shared -o structures.so guard.o singleton.o queue.o activeObject.o tcpServer.o reactor.o

# Note: Created also static libraries for my usage.

tcpServer.a: tcpServer.o
	$(STATIC) tcpServer.a tcpServer.o
tcpServer.o: tcpServer.cpp tcpServer.hpp
	$(CC) $(FLAGS) -c tcpServer.cpp $(LIB) -o tcpServer.o

reactor.a: reactor.o guard.a queue.a
	$(STATIC) reactor.a reactor.o queue.a guard.a
reactor.o: reactor.cpp reactor.hpp queue.hpp guard.hpp
	$(CC) $(FLAGS) -c reactor.cpp $(LIB) -o reactor.o

activeObject.a: activeObject.o queue.a
	$(STATIC) activeObject.a ActiveObject.o queue.a
activeObject.o: activeObject.hpp activeObject.cpp queue.hpp
	$(CC) $(FLAGS) -c activeObject.cpp $(LIB) -o activeObject.o

queue.a: queue.o guard.a
	$(STATIC) queue.a queue.o guard.a
queue.o: queue.cpp queue.hpp guard.hpp
	$(CC) $(FLAGS) -c queue.cpp $(LIB)

singleton.a: singleton.o guard.a
	$(STATIC) singleton.a singleton.o guard.a
singleton.o: singleton.cpp singleton.hpp guard.hpp
	$(CC) $(FLAGS) -c singleton.cpp $(LIB) -o singleton.o

guard.a: guard.o
	$(STATIC) guard.a guard.o
	
guard.o: guard.cpp guard.hpp
	$(CC) $(FLAGS) -c guard.cpp $(LIB) -o guard.o
	
.PHONY: clean all

clean: # Remove any file that might created.
	rm -f *.o *.a *.so *.gch
