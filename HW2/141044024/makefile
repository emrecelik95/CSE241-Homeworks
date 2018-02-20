all: main

main: main.o
	g++ main.o -o exe -std=c++11
    
main.o: main.cpp
	g++ -c main.cpp -std=c++11
    
clean: 
	rm *.o exe
