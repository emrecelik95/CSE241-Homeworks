all: exe

exe: _mainTester.o BigramMap.o BigramDyn.o MyException.o
	g++ _mainTester.o BigramMap.o BigramDyn.o MyException.o -o exe -std=c++11

_mainTester.o: _mainTester.cpp
	g++ -c _mainTester.cpp -std=c++11
	
BigramMap.o: BigramMap.cpp
	g++ -c BigramMap.cpp -std=c++11	
	
BigramDyn.o: BigramDyn.cpp
	g++ -c BigramDyn.cpp -std=c++11	

MyException.o: MyException.cpp
	g++ -c MyException.cpp -std=c++11	
	
clean: 
	rm *.o exe
