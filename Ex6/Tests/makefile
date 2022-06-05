CC = g++ -std=c++17
FLAGS = -g -Wall -pthread -fPIC 
SF = ../DataTypes

G = $(SF)/guard.hpp
Q = $(SF)/queue.hpp
S = $(SF)/singleton.hpp
AO = $(SF)/activeObject.hpp
STRUCTURES = $(SF)/structures.so

# an alias for outer folder
tests: all

all: structures activeObject queue singleton

# This is a requirement for using the shared library
structures: # Make all from inner
	 $(MAKE) -C ../DataTypes $@

singleton: singletonTest.o $(STRUCTURES)
	$(CC) $(FLAGS) -o singleton singletonTest.o $(STRUCTURES)
singletonTest.o: singletonTesting.cpp singletonTesting.hpp $(Q) $(S)
	$(CC) $(FLAGS) -c singletonTesting.cpp -o singletonTest.o

queue: queueTest.o $(STRUCTURES)
	$(CC) $(FLAGS) -o queue queueTest.o $(STRUCTURES)
queueTest.o: queueTest.cpp queueTest.hpp $(G) $(Q)
	$(CC) $(FLAGS) -c queueTest.cpp

activeObject: activeObjectTesting.o $(STRUCTURES)
	$(CC) $(FLAGS) -o activeObject activeObjectTesting.o $(STRUCTURES)	
activeObjectTest.o: activeObjectTesting.cpp activeObjectTesting.hpp $(AO) $(Q)
	$(CC) $(FLAGS) -c activeObjectTesting.cpp

.PHONY: clean all

clean: # Remove any file that might created.
	rm -rf *.o *.a *.so *.gch activeObject queue singleton
	$(MAKE) -C ../DataTypes clean 
