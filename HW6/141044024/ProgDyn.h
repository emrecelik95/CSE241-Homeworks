#ifndef PROGDYN_H
#define PROGDYN_H

using namespace std;

namespace ProgDyn{
    class CPUProgramDyn{
    public:
        CPUProgramDyn(const int &option = 0); //option alan constructor
        CPUProgramDyn(const CPUProgramDyn& dynObject); // copy constructor
        ~CPUProgramDyn();                    //destructor
        CPUProgramDyn& operator=(const CPUProgramDyn& rightSide);//assignment operator

        const string getLine(const int &lineNum)const;// istenen numaradaki satırı verir
        void ReadFile(const string &filename);         // dosya okuma fonksiyonu
        const int& size()const;                        // satır sayısını(used) return eder
        const int& getCapacity()const;                 // kapasiteyi return eder  
        void setCapacity(const int& newCapacity);      // kapasiteyi değiştirir  
        void setUsed(const int& newUsed);             // used'ı değiştirir  
        const int& getOption()const;                   // optionun getterı
        void setOption(const int &newOption);          // optionun setterı
        const string operator[](const int &lineNum)const;//getline
        const CPUProgramDyn operator+(const string& newLine);//yeni satır eklenmiş prog return et
        const CPUProgramDyn& operator+=(const string& newLine);//yeni satır ekle
        const CPUProgramDyn operator+(const CPUProgramDyn& other);//iki prog un toplamı
        bool operator==(const CPUProgramDyn& other);//iki programı karşılaştırma operatorleri
        bool operator!=(const CPUProgramDyn& other);
        bool operator<(const CPUProgramDyn& other);
        bool operator>(const CPUProgramDyn& other);
        bool operator<=(const CPUProgramDyn& other);
        bool operator>=(const CPUProgramDyn& other);
        friend ostream& operator<<(ostream& os,const CPUProgramDyn& prog);//programı print etme
        const CPUProgramDyn& operator--();          //son satırı sil (pre)
        const CPUProgramDyn operator--(int);        //son satırı sil (post)
        const CPUProgramDyn operator()(const int& start,const int& finish)const; //belli aralıktaki satırları al
    private:
        int option;     // argumandan gelen option
        string* lines;  // dynamic string array olarak instructionlar tanımlaması
        int capacity;   // stringin hafızadaki aldığı yer(kapasite)
        int used;       // kullanılan kısım(size)
        const string& addLine(const string& newLine);//yeni satır ekle
        const string& popLine();                     //son satırı sil
    };
}


#endif /* PROGDYN_H */

