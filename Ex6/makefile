CC = g++ -std=c++17
FLAGS = -g -Wall -pthread -fPIC 

DT = ./DataTypes
STRUCTURES = $(DT)/structures.so

MAIN1 = ./chainedActiveObject
MAIN1_HEADERS = $(DT)/queue.hpp $(DT)/activeObject.hpp $(DT)/tcpServer.hpp

SFM = ./SingletonFileMapping
SFM_HEADERS = $(DT)/singleton.hpp

RS = ./ReactorServer
SFM_HEADERS = $(DT)/reactor.hpp

all: structures tests client main1 singleton reactorServer

structures: # Make all from inner
	 $(MAKE) -C ./DataTypes $@
	 
tests: # Make all from inner
	 $(MAKE) -C ./Tests $@	

client:
	$(CC) client.c -o client
	
reactorServer:  reactorServer.o structures
	$(CC) $(FLAGS) -o reactorServer reactorServer.o $(STRUCTURES)
reactorServer.o: $(RS)/reactorServer.cpp $(RS)/reactorServer.hpp $(RS_HEADERS)
	$(CC) $(FLAGS) -c $(RS)/reactorServer.cpp -o reactorServer.o
	
main1:  main1.o structures
	$(CC) $(FLAGS) -o main1 main1.o $(STRUCTURES)
main1.o: $(MAIN1)/main1.cpp $(MAIN1)/main1.hpp $(MAIN1_HEADERS)
	$(CC) $(FLAGS) -c $(MAIN1)/main1.cpp -o main1.o

singleton:  singleton.o structures
	$(CC) $(FLAGS) -o singleton singleton.o $(STRUCTURES)
singleton.o: $(SFM)/singletonMmap.cpp $(SFM)/singletonMmap.hpp $(SFM_HEADERS)
	$(CC) $(FLAGS) -c $(SFM)/singletonMmap.cpp -o singleton.o

.PHONY: clean all

clean: # Remove any file that might created.
	rm -rf *.o *.a *.so *.gch client main1 singleton reactorServer
	$(MAKE) -C DataTypes clean
	$(MAKE) -C Tests clean 
