#include <iostream>
#include "Computer.h"
// parametre olarak aldıklarıyla class icindekileri ilklendiren constructor
Computer::Computer(CPU myCPU , CPUProgram myProg, Memory myMemory,const int &option){
    setCPU(myCPU);
    setCPUProgram(myProg);
    setMemory(myMemory);
    setOption(option);
    
}
// sadece option alan constructor1
Computer::Computer(const int &option){
    setOption(option); // yalnıza optionu ilklendirir
}
// tu"m islemleri gerçeklestiren fonksiyon
void Computer::execute(){
    string instruction;
    while(!myCPU.halted()){
        instruction = myProg.getLine(myCPU.getPC() - 1);
        if(!myCPU.execute(instruction,myMemory)){
            cerr << "Instruction has some invalid inputs" << " in the " << myCPU.getPC() << ".line!\n";
        }
    }
    cout << "!----->CPU HALTED<-----!\n";
    myCPU.print();
    myMemory.printAll();
}

////////////////////////////// GETTERS /////////////////////////////////////////
const CPU& Computer::getCPU(){ return myCPU; }

const CPUProgram& Computer::getCPUProgram(){ return myProg; }

const Memory& Computer::getMemory(){ return myMemory; }

const int& Computer::getOption(){ return option; }
////////////////////////////// SETTERS /////////////////////////////////////////
void Computer::setCPU(CPU currCPU){ myCPU = currCPU; }

void Computer::setCPUProgram(CPUProgram currProg){ myProg = currProg; }

void Computer::setMemory(Memory currMem){ myMemory = currMem; }

void Computer::setOption(const int& newOption){ option = newOption; }