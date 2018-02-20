#include <iostream>
#include "Memory.h"
// memoryleri ve optionu ilklendir
Memory::Memory(const int &option) {
    for(int i = 0 ; i < NUM_OF_MEMS ; i++)
        setMem(i,0);
    setOption(option);
}
// memory getterı(verilen indexteki memory'yi return eder)
const unsigned int& Memory::getMem(const int &memIndex){
    return mem[memIndex];
}
// memory setterı(verilen indexteki memory'ye value'yi atar)
void Memory::setMem(const int &memIndex,const unsigned int &newValue){
    mem[memIndex] = newValue;
}
// optionun getter ve setterı
const int& Memory::getOption() { return option; }
void Memory::setOption(const int& newOption) { option = newOption; }
// tum memoryleri ekrana basar
void Memory::printAll(){
    cout << "Memory Values:";
    for(int i = 0 ; i < NUM_OF_MEMS ; i++){
        if(i% 5 == 0)
            cout << endl;
        cout << "[" << i << "]" << " -> " << getMem(i) << "  ";
    }
    cout << endl;
}