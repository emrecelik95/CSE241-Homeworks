#include <iostream>
#include <string>
#include "CPU.h"            //CPU CLASSI
#include "CPUProgram.h"     //CPUProfram CLASI
#include "Memory.h"         //Memory  CLASSI
#include "MyFuncs.h"        //Kendi fonsksiyonlarım(strtoint,lowtoup,commaExist)
#include "Computer.h"       //Computer CLASSI
using namespace std;

int main(int argc, char** argv) {
    string filename = static_cast<string>(argv[1]),instruction;
    int option = myStrToInt(argv[2]);
 // ARGUMAN HATASI KONTROLLERI
    if(argc != 3){
        cerr << "Invalid arguments!\n";
        return -1;
    }
    if(option != 0 && option != 1 && option != 2){
        cerr << "Option must be 0 or 1\n";
        return -1;
    }
    

    //Testing class Computer
    Memory myMemory(option);
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    
    Computer myComputer1(myCPU,myCPUProgram,myMemory,option);
    Computer myComputer2(option);
    
    myComputer2.setCPU(myComputer1.getCPU());
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory());
    
    myComputer2.execute();

    return 0;
    
}
