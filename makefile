CC = g++ -std=c++17
FLAGS = -pthread -fPIC 
OPTIONS = -g -Wall

ROOT = ./Ex6
DT = $(ROOT)/DataTypes
SFM = $(ROOT)/SingletonFileMapping
RS = $(ROOT)/ReactorServer
MAIN1_DIR = $(ROOT)/chainedActiveObject

define makeEx6
    $(MAKE) -C $(ROOT) $(1)
endef

all: main1.c guard.cpp singleton.cpp reactor.cpp

main1.c: main1


guard.cpp:
	cp $(DT)/guard.cpp guard.cpp
	cp $(DT)/guard.hpp guard.hpp
singleton.cpp:
	cp $(DT)/singleton.cpp singleton.cpp
	cp $(DT)/singleton.hpp singleton.hpp
	cp $(SFM)/singletonMmap.cpp singeltonMmap.cpp
	cp $(SFM)/singletonMmap.hpp singeltonMmap.hpp

main1: client
	$(call makeEx6, $@) # $@ is the label name
	cp $(MAIN1_DIR)/main.cpp main1.cpp
	cp $(MAIN1_DIR)/main.hpp main1.hpp
	echo "File at $(ROOT)/$@ and requires to be at this relative path."

reactor.cpp: client
	cp $(DT)/reactor.cpp reactor.cpp
	cp $(DT)/reactor.hpp reactor.hpp
	cp $(RS)/reactorServer.cpp reactorServer.cpp
	cp $(RS)/reactorServer.hpp reactorServer.hpp
	$(call makeEx6, $@)

client: 
	$(call makeEx6, $@)
	cp $(ROOT)/client.c client.c

tests:
	$(call makeEx6, $@)
	echo "All tests files are located at $(ROOT)/Tests"

.PHONY: clean all

clean:
	rm -f *.o *.a *.so *.gch *.cpp *.hpp *.c
	$(MAKE) -C Ex6 clean
