#include <iostream>
#include <fstream>
#include "CPUProgram.h"

using namespace std;

CPUProgram ::CPUProgram(const int &option){
    setOption(option); // optionu class icindeki optiona ata
}
// optionun getter ve setterı
const int& CPUProgram::getOption()const { return option; } 

void CPUProgram::setOption(const int& newOption) { option = newOption; } 

// dosyayı oku ve satırları vektor de  tut
void CPUProgram::ReadFile(const string &filename){
    fstream theFile;
    int i = 0;
    string line;
    theFile.open(filename);
    if(!theFile.is_open()){ // dosya açılmama kontrolu
        cerr << "File Couldn't be opened\n";
        exit(1);
    }
    while(!theFile.eof()){ // satırları lines'a teker teker at
        getline(theFile,line);
        lines.push_back(line);
        i++;
    }
    lines.pop_back();             // fazladan eklenen son satırı silmek için
    theFile.close();
}
// satır sayısını return et
const int CPUProgram::size()const{
    return lines.size();  // vektorun size ını return et
    
}
//verilen numaradaki satırı dondur
const string CPUProgram::getLine(const int &lineNum)const{
    if(lineNum < 0 || lineNum >= size()){
        cerr << "Invalid Line Number!\n";
        return "";
    }
    return lines[lineNum];    
}
const string CPUProgram::operator [](const int& lineNum)const{ 
    return getLine(lineNum);        // getline degerini return et
}
//
const CPUProgram CPUProgram::operator +(const string& newLine){
    CPUProgram newProg = *this;      // degiskene kopyala
    if(newLine == "")
        cerr << "Invalid String!\n";
    else
        newProg.lines.push_back(newLine);// ekleme islemi
    return newProg;                  //  eklenmis halini return et
}
const CPUProgram& CPUProgram::operator +=(const string& newLine){
    if(newLine == "")
        cerr << "Invalid String!\n";
    else
        lines.push_back(newLine);       // yeni satırı ekle
    return *this;                   // eklenmiş halini return et
}
const CPUProgram CPUProgram::operator +(const CPUProgram& other){
    CPUProgram newProg = *this;     // degiskene kopyala
    for(int i = 0 ; i < other.size() ; i++) // ne kadar satır varsa o kadar dön
        newProg.lines.push_back(other.getLine(i)); // birincinin üstüne ikinciyi ekle
    return newProg;                 // eklenmiş halini return et
}
// (Karşılaştırma Operatorleri) satır sayılarını kıyasla
bool CPUProgram::operator ==(const CPUProgram& other){
    return (size() == other.size());   
}
bool CPUProgram::operator !=(const CPUProgram& other){
    return (size() != other.size());
}
bool CPUProgram::operator <(const CPUProgram& other){
    return (size() < other.size());
}
bool CPUProgram::operator >(const CPUProgram& other){
    return (size() > other.size());
}
bool CPUProgram::operator <=(const CPUProgram& other){
    return (size() <= other.size());
}
bool CPUProgram::operator >=(const CPUProgram& other){
    return (size() >= other.size());
}
const CPUProgram& CPUProgram::operator --(){
    if(size() == 0)
        cerr << "There is no line to delete!\n";
    else
        lines.pop_back();   // son satırı sil
    return *this;           // silinmiş halini return et
}
const CPUProgram CPUProgram::operator --(int empty){
    CPUProgram tempProg = *this;// degiskene kopyala
    if(size() == 0)
        cerr << "There is no line to delete!\n";
    else
        lines.pop_back();           // son satırı sil
    return tempProg;            // silinmemiş halini return et
}
const CPUProgram CPUProgram::operator ()(const int& start, const int& finish){
    CPUProgram newProg;
    if(start > finish || start < 0 || finish < 0 || finish >= size())
        cerr << "Invalid Boundaries!\n";
    else
        for(int i = start ; i <= finish; i++) // aralıktaki satırları yeni prog'a aktar
            newProg.lines.push_back(lines[i]);
    return newProg;                       // yeni prog u return et
}
ostream& operator<<(ostream& os,const CPUProgram& prog){
    for(int i = 0; i < prog.size() ; i++) // satırların hepsini ekrana bas
        os << prog.lines[i] << endl;
    return os;                            // ostream return et
}
