#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <vector>

using namespace std;

class CPUProgram {
public:
    CPUProgram(const string &filename); // constructor readFile'ı çağırıyor
    string getLine(const int &lineNum); // istenen numaradaki satırı verir
private:
    int size(); // satır sayısını return eder
    vector<string> lines;  // vector turunde instructionlar tanımlaması
    int numOfLines = 0;     // satır sayısı degisken olarak
    bool readFile(const string &filename); // dosya okuma fonksiyonu
};

#endif

