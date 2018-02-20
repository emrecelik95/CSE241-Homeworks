#ifndef COMPUTER_H
#define COMPUTER_H
// cpu cpuprogram ve memory classlarını kullanacak
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

using namespace std;

class Computer {
public:
    Computer(CPU myCPU , CPUProgram myProg, Memory myMemory,const int &option = 0);//parametre alan constructor
    Computer(const int &option = 0);    // sadece option constructor
    void execute();                 // programı calıstıran islemleri yapan fonksiyon
    const CPU& getCPU();                   // myCPU nun getterı
    void setCPU(CPU currCPU);       // myCPU nun setterı
    const CPUProgram& getCPUProgram();     // myProg un getterı
    void setCPUProgram(CPUProgram currProg);    // myProg un setterı
    const Memory& getMemory();             // myMemory nin getteri
    void setMemory(Memory currMem); // myMemory nin setteri
    const int& getOption();                // optionun getterı
    void setOption(const int &newOption); // optionun setterı
private:
    CPU myCPU;                      // CPU objesi
    CPUProgram myProg;              // CPUProgram objesi
    Memory myMemory;                // Memory objesi
    int option;                     // argumandan gelen option
};

#endif