#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <vector>

using namespace std;

class CPUProgram {
public:
    CPUProgram(const int &option = 0);
    const string getLine(const int &lineNum)const;// istenen numaradaki satırı verir
    void ReadFile(const string &filename);         // dosya okuma fonksiyonu
    const int size()const;                         // satır sayısını return eder
    const int& getOption()const;                   // optionun getterı
    void setOption(const int &newOption);          // optionun setterı
    const string operator[](const int &lineNum)const;//getline
    const CPUProgram operator+(const string& newLine);//yeni satır eklenmiş prog return et
    const CPUProgram& operator+=(const string& newLine);//yeni satır ekle
    const CPUProgram operator+(const CPUProgram& other);//iki prog un toplamı
    bool operator==(const CPUProgram& other);//iki programı karşılaştırma operatorleri
    bool operator!=(const CPUProgram& other);
    bool operator<(const CPUProgram& other);
    bool operator>(const CPUProgram& other);
    bool operator<=(const CPUProgram& other);
    bool operator>=(const CPUProgram& other);
    friend ostream& operator<<(ostream& os,const CPUProgram& prog);//programı print etme
    const CPUProgram& operator--();          //son satırı sil (pre)
    const CPUProgram operator--(int);        //son satırı sil (post)
    const CPUProgram operator()(const int& start,const int& finish); //belli aralıktaki satırları al
private:
    int option;            // argumandan gelen option
    vector<string> lines;  // vector olarak instructionlar tanımlaması
};

#endif
