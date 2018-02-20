#include <iostream>
#include <fstream>
#include "CPUProgram.h"

using namespace std;

CPUProgram ::CPUProgram(const int &option){
    setOption(option); // optionu class icindeki optiona ata
}
// optionun getter ve setterı
int CPUProgram::getOption() { return option; } 

void CPUProgram::setOption(const int& newOption) { option = newOption; } 

// dosyayı oku ve satırları vektor de  tut
bool CPUProgram::ReadFile(const string &filename){
    fstream theFile;
    int i = 0;
    string line;
    theFile.open(filename);
    if(!theFile.is_open()){ // dosya açılmama kontrolu
        cerr << "File Couldn't be opened\n";
        return false;
    }
    while(!theFile.eof()){ // satırları lines'a teker teker at
        getline(theFile,line);
        lines.push_back(line);
        i++;
    }
    numOfLines = i - 1;   // okunan satır sayısını size'a ata
    theFile.close();
    return true;
}
// satır sayısını return et
int CPUProgram::size(){ 
    return numOfLines;           
}
//verilen numaradaki satırı dondur
string CPUProgram::getLine(const int &lineNum){
    return lines[lineNum];    
}