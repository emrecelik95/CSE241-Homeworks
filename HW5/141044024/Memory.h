#ifndef MEMORY_H
#define MEMORY_H

using namespace std;
const int NUM_OF_MEMS = 50;

class Memory {
public:
    Memory(const int &option = 0);    // option alan constructor
    const unsigned int& getMem(const int &memIndex);   //memory getter fonksiyonu
    void setMem(const int &memIndex,const unsigned int &newValue);  // memory setter fonsiyonu
    void printAll();    // tum memoryleri ekrana basan fonksiyon
    const int& getOption();                        // optionun getterı
    void setOption(const int &newOption);   // optionun setterı
private:
    unsigned int mem[NUM_OF_MEMS];  // dizi olarak memory tanımlaması
    int option;                  // argumandan gelen option
};

#endif