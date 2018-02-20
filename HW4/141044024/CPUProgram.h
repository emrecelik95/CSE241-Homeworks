#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <vector>

using namespace std;

class CPUProgram {
public:
    CPUProgram(const int &option = 0); // constructor readFile'ı çağırıyor
    string getLine(const int &lineNum); // istenen numaradaki satırı verir
    bool ReadFile(const string &filename); // dosya okuma fonksiyonu
    int size(); // satır sayısını return eder
    int getOption();                        // optionun getterı
    void setOption(const int &newOption);   // optionun setterı
private:
    int option;            // argumandan gelen option
    vector<string> lines;  // vector olarak instructionlar tanımlaması
    int numOfLines = 0;    // satır sayısı
};

#endif

