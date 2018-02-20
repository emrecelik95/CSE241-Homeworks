#include <iostream>
#include <string>
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 3){
        cerr << "İnvalid arguments!\n";
        return -1;
    }
    if(static_cast<string>(argv[2])!= "0" && static_cast<string>(argv[2])!= "1"){
        cerr << "Option must be 0 or 1\n";
        return -1;
    }
    CPUProgram myProg(static_cast<string>(argv[1]));
    CPU myCPU(static_cast<string>(argv[2]));
    
    while(!myCPU.halted()){
        string instruction = myProg.getLine(myCPU.getPC());
        if(!myCPU.execute(instruction)){
            cerr << "Instruction has some invalid inputs!\n";
        }
    }
    return 0;
}
