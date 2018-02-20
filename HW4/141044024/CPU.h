#ifndef CPU_H
#define CPU_H
#include "Memory.h"   // memory kullanılacak
using namespace std;

const int NUM_OF_REGS = 5;

class CPU {
public:
    CPU(const int &option = 0); // constructor , parametre olarak option alıyor
    int getPC();    // program counterı veren getter
    bool halted();  // program bitti kontrolu
    bool execute(string line,Memory &myMemory);  // instructionın çalıştırılması
    void print();   // registerlar ve pc nin yazdırılması
    int getOption();                // optionun getterı
    void setOption(const int &newOption);   // optionun setterı
private:
    int option;
    int pc;
    int regs[NUM_OF_REGS];
    bool hlt = false;
    bool getHLT();                  // hlt degiskeninin getteri
    void setHLT(bool isHalted);     // hlt degiskeninin setteri
    int getReg(const string &currReg); // registerın tuttuğu değeri return eder
    void setPC(const int &newPc);  // pc yi degistirir
    int readIns(const string &line,string &currIns);// line daki instructionu okur (currIns) ve aktif indisi return eder
    int readReg(const string &line,string &currReg);// line daki registerı okur (currReg) ve aktif indisi return eder
    int readVal(const string &line,string &currVal);// line daki 2.degeri okur (currVal) ve aktif indisi return eder
    bool checkEofLine(const string &line); //ikinci degerden sonra hata kontrolu
    void mov(const string &reg,const int &val); // registera atama(mov) islemi
    void add(const string &reg,const int &val); // register degerini arttırma islemi
    void sub(const string &reg,const int &val); // register degerini azaltma islemi
    void prn(const string &currVal,const unsigned int &mem); // const veya register degerini yazma islemi
    void jmp(const int &lineNum); // verilen satır sayısına atlama islemi
    void jmp(const int &lineNum,const string &reg); // register 0 ise aynı islem
    void jpn(const int& lineNum,const string &reg); // register 0 veye daha kücükse aynı islem
    bool isNumber(const string &str); // stringin sayı olma kontrolu
    bool isRegister(const string &str); // stringin register olma kontrolu
    bool isMemory(const string &str);   // stringin memory olma kontrolu
};



#endif
