#include <iostream>
#include <fstream>
#include "ProgDyn.h"

namespace ProgDyn{
    
    CPUProgramDyn ::CPUProgramDyn(const int &option):capacity(10),used(0){
        setOption(option); // optionu class icindeki optiona ata
        lines = new string[getCapacity()]; //kapasite kadar yer al
    }
    //copy constructor,yeni olusturulan objeye digerinin herseyini kopyala 
    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& dynObject){
        setCapacity(dynObject.getCapacity());
        setUsed(dynObject.size());
        lines = new string[getCapacity()];
        for(int i = 0;i < size();i++)
            lines[i] = dynObject.lines[i];
    }
    // destructor,aldığın memoryi serbest bırak
    CPUProgramDyn::~CPUProgramDyn(){delete[] lines;} 
    // assignment operatoru,kapasite aynı olmak sartıyla sagdakini soldakine kopyala
    CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn& rightSide){
        if(getCapacity()!=rightSide.getCapacity()){
            delete[] lines;
            lines = new string[rightSide.getCapacity()];
        }
        setCapacity(rightSide.getCapacity());
        setUsed(rightSide.size());
        for(int i = 0;i < size();i++)
            lines[i] = rightSide.lines[i];
        
        return *this;
    }
    // optionun getterı
    const int& CPUProgramDyn::getOption()const { return option; } 
    // optionun setterı
    void CPUProgramDyn::setOption(const int& newOption) { option = newOption; } 

    // dosyayı oku ve satırları dinamik string array de  tut
    void CPUProgramDyn::ReadFile(const string &filename){
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
            if(!theFile.eof())     // sonda eklenen boş satırı almamak için
                addLine(line);     // member function(satırı stringe ekle)
            i++;
        }
        theFile.close();
    }
    // satır sayısını(stringin size'ı yani used) return et
    const int& CPUProgramDyn::size()const{return used;}
    // capacity getter
    const int& CPUProgramDyn::getCapacity() const{return capacity;}
    // capacity setter
    void CPUProgramDyn::setCapacity(const int& newCapacity){capacity = newCapacity;}
    // used setterı
    void CPUProgramDyn::setUsed(const int& newUsed){used = newUsed;}
    //verilen numaradaki satırı dondur
    const string CPUProgramDyn::getLine(const int &lineNum)const{
        if(lineNum < 0 || lineNum >= size()){
            cerr << "Invalid Line Number!\n";
            return "";
        }
        return lines[lineNum];    
    }
    const string CPUProgramDyn::operator [](const int& lineNum)const{ 
        return getLine(lineNum);        // getline degerini return et
    }
    //
    const CPUProgramDyn CPUProgramDyn::operator +(const string& newLine){
        CPUProgramDyn newProg = *this;      // degiskene kopyala
        if(newLine == "")
            cerr << "Invalid String!\n";
        else
            newProg.addLine(newLine);    // ekleme islemi
        return newProg;                  //  eklenmis halini return et
    }
    const CPUProgramDyn& CPUProgramDyn::operator +=(const string& newLine){
        if(newLine == "")
            cerr << "Invalid String!\n";
        else
            addLine(newLine);           // yeni satırı ekle
        return *this;                   // eklenmiş halini return et
    }
    const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& other){
        CPUProgramDyn newProg = *this;     // degiskene kopyala
        for(int i = 0 ; i < other.size() ; i++) // ne kadar satır varsa o kadar dön
            newProg.addLine(other.getLine(i)); // birincinin üstüne ikinciyi ekle
        return newProg;                 // eklenmiş halini return et
    }
    // (Karşılaştırma Operatorleri) satır sayılarını kıyasla
    bool CPUProgramDyn::operator ==(const CPUProgramDyn& other){
        return (size() == other.size());   
    }
    bool CPUProgramDyn::operator !=(const CPUProgramDyn& other){
        return (size() != other.size());
    }
    bool CPUProgramDyn::operator <(const CPUProgramDyn& other){
        return (size() < other.size());
    }
    bool CPUProgramDyn::operator >(const CPUProgramDyn& other){
        return (size() > other.size());
    }
    bool CPUProgramDyn::operator <=(const CPUProgramDyn& other){
        return (size() <= other.size());
    }
    bool CPUProgramDyn::operator >=(const CPUProgramDyn& other){
        return (size() >= other.size());
    }
    const CPUProgramDyn& CPUProgramDyn::operator --(){
        if(size() == 0)
            cerr << "There is no line to delete!\n";
        else
            popLine();          // son satırı sil(member function)
        return *this;           // silinmiş halini return et
    }
    const CPUProgramDyn CPUProgramDyn::operator --(int empty){
        CPUProgramDyn tempProg = *this;// degiskene kopyala
        if(size() == 0)
            cerr << "There is no line to delete!\n";
        else
            popLine();              // son satırı sil
        return tempProg;            // silinmemiş halini return et
    }
    const CPUProgramDyn CPUProgramDyn::operator ()(const int& start, const int& finish)const{
        CPUProgramDyn newProg;
        if(start > finish || start < 0 || finish < 0 || finish >= size())
            cerr << "Invalid Boundaries!\n";
        else
            for(int i = start ; i <= finish; i++) // aralıktaki satırları yeni prog'a aktar
                newProg.addLine(lines[i]);
        return newProg;                       // yeni prog u return et
    }
    ostream& operator<<(ostream& os,const CPUProgramDyn& prog){
        for(int i = 0; i < prog.size() ; i++) // satırların hepsini ekrana bas
            os << prog.lines[i] << endl;
        return os;                            // ostream return et
    }
    // yeni satır ekle
    const string& CPUProgramDyn::addLine(const string& newLine){
        if(size() >= getCapacity()){    //yer dolduysa 2 katı kadar yer al
            setCapacity(getCapacity() * 2);
            string* newLines = new string[getCapacity()]; // once temp olustur
            for(int i = 0;i < size();i++)                 // herseyi tempe at
                newLines[i] = lines[i];
            delete[] lines;                               // eskisini sil
            
            lines = newLines;                             // bunu lines'a at
        }
        lines[used] = newLine;  // sıradaki indisteki yere satırı ekle
        setUsed(used + 1);      // indisi 1 arttır
        return *lines;          // stringi dondur
    }
    
    const string& CPUProgramDyn::popLine(){
        lines[size() - 1] = "";     // silinecek yeri bosalt
        setUsed(size() - 1);        // used'ı 1 azalt
        return *lines;              // stringi dondur
    }
}