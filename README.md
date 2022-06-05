OS Ex6


Assuming:
- We can use C++ in every question (I asked Yuval and he allowed).
- We can name main1.c elements in any name (as Noa sent by mail).

IMPORTANT: 
gcc did not work while using -lstdc++;
It gave me missing functions in system libraries, the only solution I found was using g++.
You may try changing the compiler to your prefered compiler but it didn't work for me.
Tested in Ubuntu 20.04 LTS & macOS, both working with g++ and not gcc. (perhaps the usage of c++17 ?)

MAKEFILES:
You can make the (basic) required files using the makefile here.
Use `make <filename>` to make the required file: main1.c (*), singleton.cpp, reactor.cpp, guard.cpp
You can also enter the Ex6 directory and make any file you want using its makefile.

To remove them use `make clean`.

****(*)main1.c****: main1.c is named main1.cpp at Ex6/chainedActiveObject/ directory.
 code and exectuable can be made by using `make main1` or `make main1.c` in this directory.
 
client will be copied and created by using `make reactor` and `make main1`, reactorServer will also be created by `make reactor`
  
***Tests are located at /Ex6/Tests and can be built by `make tests` either here or by ./Ex6/makefile***

  
Although developed in OOP style, I also created alias functions for enQ, deQ as required.
 
 reactorServer is also reactor testing since the reactor need to have request/respond in order to work with poll. It is as easy and simple as testing with files so I count that as a testing program.

Structure:
- makefile
- Ex6:
 	- DataTypes:
	
 		- makefile
 		
		
		 - activeObject.cpp
		 - activeObject.hpp
		 
		 
	 	- guard.cpp
	 	- guard.hpp
		
		
	 	- queue.cpp
	 	- queue.hpp
		
		
	 	- reactor.cpp
	 	- reactor.hpp
		
		
	 	- singleton.cpp
	 	- singleton.hpp
		
		
	 	- tcpServer.cpp
	 	- tcpServer.hpp
	
	- ReactorServer:
	 	- reactorServer.cpp
	 	- reactorServer.hpp
	- pollServer:
	 	- pollServer.cpp
	 	- pollServer.hpp
	- SingletonFileMapping:
	 	- singletonMmap.cpp
	 	- singletonMmap.hpp
	- Tests:
	 	- makefile
	 	
		
	 	- activeObjectTesting.cpp
	 	- activeObjectTestiung.hpp
	 	
		
	 	- queueTest.cpp
	 	- queueTest.hpp
	 	
		
	 	- singletonTesting.cpp
	 	- singlettonTesting.hpp
	 	
	 	
