CC = g++
FLAGS = -g -Wall -pthread -fPIC 

DT = ./DataTypes
MAIN1 = ./chainedActiveObject
STRUCTURES = $(DT)/structures.so
HEADERS = $(DT)/queue.hpp $(DT)/activeObject.hpp $(DT)/tcpServer.hpp

all: structures tests client main1

structures: # Make all from inner
	 $(MAKE) -C ./DataTypes $@
	 
tests: # Make all from inner
	 $(MAKE) -C ./Tests $@	

client:
	$(CC) client.c -o client
	
main1:  main1.o structures
	$(CC) $(FLAGS) -o main1 main1.o $(STRUCTURES)
main1.o: $(MAIN1)/main1.cpp $(MAIN1)/main1.hpp $(HEADERS)
	$(CC) $(FLAGS) -c $(MAIN1)/main1.cpp -o main1.o

.PHONY: clean all

clean: # Remove any file that might created.
	rm -rf *.o *.a *.so *.gch client main1
	$(MAKE) -C DataTypes clean
	$(MAKE) -C Tests clean 
