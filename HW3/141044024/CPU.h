#ifndef CPU_H
#define CPU_H

using namespace std;

const int NUM_OF_REGS = 5;

class CPU {
public:
    CPU(const string &op); // constructor , parametre olarak option alıyor
    int getPC();    // program counterı veren getter
    bool halted();  // program bitti kontrolu
    bool execute(string &line);  // instructionın çalıştırılması
private:
    string option;
    int pc;
    int regs[NUM_OF_REGS];
    string currIns;  // aktif satırdaki instruction
    string currReg;  // aktif satırdaki register
    string currVal;  // aktif satırdaki value(const veya register valuesi)
    int getReg(const string &currReg); // registerın tuttuğu değeri return eder
    void setPC(const int &newPc);  // pc yi degistirir
    void print();   // registerlar ve pc nin yazdırılması
    int readIns(const string &line);// line daki instructionu okur (currIns) ve aktif indisi return eder
    int readReg(const string &line);// line daki registerı okur (currReg) ve aktif indisi return eder
    int readVal(const string &line);// line daki 2.degeri okur (currVal) ve aktif indisi return eder
    bool checkEofLine(const string &line); //ikinci degerden sonra hata kontrolu
    void mov(const string &reg,const int &val); // registera atama(mov) islemi
    void add(const string &reg,const int &val); // register degerini arttırma islemi
    void sub(const string &reg,const int &val); // register degerini azaltma islemi
    void prn(const string &currVal); // const veya register degerini yazma islemi
    void jmp(const int &lineNum); // verilen satır sayısına atlama islemi
    void jmp(const int &lineNum,const string &reg); // register 0 ise aynı islem
    bool isNumber(const string &strNum); // stringin sayı olma kontrolu
    bool isRegister(const string &reg); // stringin register olma kontrolu
};



#endif
