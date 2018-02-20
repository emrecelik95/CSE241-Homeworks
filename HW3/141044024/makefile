all: main

main: main.o CPU.o CPUProgram.o MyFuncs.o
	g++ main.o CPU.o CPUProgram.o MyFuncs.o -o exe -std=c++11
    
main.o: main.cpp
	g++ -c main.cpp -std=c++11
    
CPU.o: CPU.cpp
	g++ -c CPU.cpp -std=c++11

CPUProgram.o: CPUProgram.cpp
	g++ -c CPUProgram.cpp -std=c++11
	
MyFuncs.o: MyFuncs.cpp
	g++ -c MyFuncs.cpp -std=c++11

clean: 
	rm *.o exe
