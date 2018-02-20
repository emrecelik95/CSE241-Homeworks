#include <iostream>
#include "CPU.h"
#include "MyFuncs.h"  // commaExist , myStrToInt , lowToUp fonksyionları
using namespace std;
// Option alan constructor,registerları,pcyi ve optionu ilklendirir
CPU::CPU(const int &option) {
    for(int i=0;i<NUM_OF_REGS;i++) // registerlara 0 atama
        regs[i] = 0;
    setPC(1);                          // pc'ye 1 atama
    setOption(option);                  // optiona konsoldan gelen degeri atama
}
// pc nin getter fonksyionu
const int& CPU::getPC(){
    return pc;      // pc yi return etme
}
// pc nin setter fonksiyonu
void CPU::setPC(const int &newPc){
    pc = newPc;     // pc yi degistirme
    if(getHLT()) // halt olunca pc ilerlemesin
        pc--;
}
// optionun getter ve setterı
void CPU::setOption(const int& newOption) { option = newOption; }

const int& CPU::getOption() { return option; }

//registerların getter fonksiyonu
int CPU::getReg(const string &reg){
    return regs[myStrToInt(&reg[1]) - 1];   // aktif registerı dondurme
}
//registerların setter fonksiyonları
void CPU::mov(const string &reg,const int &val){
    regs[myStrToInt(&reg[1]) - 1] = val;    // aktif registera deger atama
}

void CPU::add(const string &reg,const int &val){
    regs[myStrToInt(&reg[1]) - 1] += val;   // aktif registerı arttırma
}

void CPU::sub(const string &reg,const int &val){
    regs[myStrToInt(&reg[1]) - 1] -= val;   // aktif registerı azaltma
}
//ekrana register veya memory veya const basan komutun fonksiyonu
void CPU::prn(const string &currVal,const unsigned int &mem){
//  deger registersa veya const sa degeri yaz,degilse false dondur
    if(isRegister(currVal))                 
        cout <<  getReg(currVal) << endl;
    else if(isMemory(currVal))
        cout << mem << endl;
    else if(isNumber(currVal))
        cout << currVal << endl;
}
//verilen line adrese atlar
void CPU::jmp(const int &lineNum){
    setPC(lineNum);        // pc yi istenen satır numarasını ata
}
//aynı islemi register 0 ise yapar
void CPU::jmp(const int &lineNum,const string &reg){
    if(getReg(reg) == 0){
        setPC(lineNum);     // aynı atamayı register degeri 0 ise yap
    }
}
// aynı islemi register 0 veya 0 dan kucukse yapar
void CPU::jpn(const int& lineNum,const string &reg){
    if(getReg(reg) <= 0)
        setPC(lineNum);
}
// program hlt oldumu olmadımı bilgi veren bool fonksiyon
bool CPU ::halted(){
    if(getHLT())// HLT ise print i çağır ve true dondur
        return true;
    return false;
}
//registerları ve pc yi ekrana basan fonksiyon
void CPU::print(){        // registerları ve pc yi ekrana bas
    cout << "CPU Register Values:" << endl;
    for(int i = 0 ; i < NUM_OF_REGS ; i++)
        cout << "[" << i << "]" << " -> " << regs[i] << "  ";
    cout << endl;
}
// hlt degiskeninin setterı
void CPU::setHLT(bool isHalted){
    hlt = isHalted;
}
// hlt degiskeninin getterı
bool CPU::getHLT(){
    return hlt;
}
// instructionu işleyen fonksiyon
bool CPU ::execute(string line,Memory &currMemory)
{
    int i = 0,value = 0;    // i:satırdaki aktif karakter indexi,value:aktif deger
    bool error = false;     // hata denetim degiskeni
    string currIns;  // aktif satırdaki instruction
    string currReg;  // aktif satırdaki ilk string
    string currVal;  // aktif satırdaki value(const veya register(veya memory) values)
    
    line = lowToUp(line);   // satırdaki küçük harfleri(varsa) büyüt
    i += readIns(line,currIns);     // instructionu oku ve aktif indexi i'ye ekle
    if(getOption() == 1 || getOption() == 2){ // option 1 veya 2 ise pc yi print et
        for(int i = 0;line[i]!=';' && line[i]!='\0';i++)
            cout << line[i];
        cout << " - " << "PC:" << pc << endl;
    }
// mov,add veya sub ise registerı oku ,hata kontrolü yap,fonksiyon çağır    
    if(currIns == "MOV" || currIns == "ADD" || currIns == "SUB")
    {
        i += readReg(&line[i],currReg);
        if(!isRegister(currReg) && !isMemory(currReg))
            error = true;
        else if(isMemory(currReg) && (currIns == "ADD" || currIns == "SUB")){
            error = true;
        }
        else{                                // degeri al ve hata kontrolleri yap
            i += readVal(&line[i],currVal);  // virgülü geçtikten sonra degeri oku
            if(!isRegister(currVal) && !isNumber(currVal) && !isMemory(currVal))
                error = true;
            else if(!checkEofLine(&line[i]))
                error = true;    
        }
        if(!error){                          // hata yoksa devam et 
            if(isRegister(currVal))
                value = getReg(currVal);
            else if(isNumber(currVal))
                value = myStrToInt(currVal);
            else if(isMemory(currVal))
                value = currMemory.getMem(myStrToInt(&currVal[1]));
            if(currIns == "ADD")
                add(currReg,value);
            else if(currIns == "SUB")
                sub(currReg,value);
            else if(currIns == "MOV"){ // ikinci değer register veya memory ise 1'i 2'ye at
                if(isRegister(currReg)){
                    if(isRegister(currVal)){
                        value = getReg(currReg);
                        currReg = currVal;
                        mov(currReg,value);
                    }
                    else if(isMemory(currVal)){
                        value = getReg(currReg);
                        currMemory.setMem(myStrToInt(&currVal[1]),value);
                    }
                    else if(isNumber(currVal)){
                        mov(currReg,value);
                    }
                }
                else if(isMemory(currReg)){
                    if((isRegister(currVal))){
                        value = currMemory.getMem(myStrToInt(&currReg[1]));
                        mov(currVal,value);
                    }
                    else if(isMemory(currVal)){;
                        value = currMemory.getMem(myStrToInt(&currReg[1]));
                        currMemory.setMem(myStrToInt(&currVal[1]),value);
                    }
                    else if(isNumber(currVal)){
                        currMemory.setMem(myStrToInt(&currReg[1]),value);
                    }
                }
            }
        }
    }
    else if(currIns == "PRN") // prn ise degeri oku ve ekrana bas
    {
        i += readVal(&line[i],currVal); // degeri al
        if(!checkEofLine(&line[i]))     // hata kontrolleri
            error = true;
        else if(!isRegister(currVal) && !isNumber(currVal) && !isMemory(currVal))
            error = true;
        else                        // hata yoksa prn yi çağır ekrana gerekli degeri
            prn(currVal,currMemory.getMem(myStrToInt(&currVal[1])));
    }
    else if(currIns == "JMP" || currIns == "JPN")//jmp ise virgül olma durumuna göre jmp fonksyionu çağır
    {
        if(currIns == "JPN" && !commaExist(line)) // JPN yalnızca kosula baglıdır,JPN 2 gecersiz
            return false;
        
        if(commaExist(line))// virgül varsa registerı al,syntax hatası yoksa jmp veya jpn fonksiyonunu çağır
        {
            i += readReg(&line[i],currReg);
            if(!isRegister(currReg))
                error = true;
            else{
                i += readVal(&line[i],currVal);
                if(!checkEofLine(&line[i]))
                    error = true;
                else if(!isNumber(currVal))
                    error = true;
            }
            if(!error){
                value = myStrToInt(currVal);
                if(currIns == "JPN")
                    jpn(value - 1,currReg);
                else
                    jmp(value - 1,currReg); // aşağıda 1 artacağı için 1 azaltıldı
            }
        }
        else    // virgül yoksa direk degeri al,syntax hatası yoksa jmp yi çağır
        {
            i += readVal(&line[i],currVal);
            if(!checkEofLine(&line[i]))
                    error = true;
            else if(!isNumber(currVal))
                error = true;
            else{
                value = myStrToInt(currVal);
                jmp(value - 1);        // aşağıda 1 artacağı için 1 azaltıldı
            }
        }
    }
    else if(currIns == "HLT") // registerların ve pc nin son durumunu ekrana bas 
    {
        setHLT(true);         // hlt degiskenini true yap
        if(!checkEofLine(&line[i])){    // syntax hata kontrolu
            error = true;
        }
    }
    else // current instruction(currIns) yanlıs ise error true yap
        error = true;
    // currIns prn degil se yazma islemi burada gerçekleşir(düzen için)
    if((getOption() == 1 || getOption() == 2)){
        print();
        if(getOption() == 2)
            currMemory.printAll();
    }
    if(error)   // hata varsa program halt olsun
        setHLT(true);
    else        // hata yoksa pc yi 1 arttır      
        setPC(pc + 1);
    return !error;    // error yok ise fonksiyon true dondursun
}
// instructionu oku ve aktif indexi return et
int CPU::readIns(const string &line,string &currIns){ 
    int i;
    bool readed = false; // mo v gibi hataların kontrolu(aralarda bosluk durumu)
    currIns = "";
    for(i=0;!(readed== true && line[i]== ' ')&&line[i]!= '\0';i++){
        if(line[i]!= ' '){
            currIns += line[i];
            readed = true;
        }
    }
    return i;
}
//registerı oku ve aktif index + 1(virgül den dolayı) return et
int CPU::readReg(const string &line,string &currReg){
    int i;
    bool readed = false,readedSpc = false;
    currReg = "";
    for(i=0;!(readed== true && line[i]==',') && line[i]!= '\0';i++){
        if(line[i]!= ' '){
            if(readedSpc == true)
                return -1;
            currReg += line[i];
            readed = true;
        
        }
        if(readed == true && line[i] == ' ')
            readedSpc = true;
    }

    return i+1;
}
// value'yi oku ve aktif indexi return et
int CPU::readVal(const string &line,string &currVal){ 
    int i;
    bool readed = false;
    currVal = "";
    for(i=0;!(readed== true && line[i]== ' ')&&line[i]!= '\0'&&line[i]!=';';i++){
        if(line[i]!= ' '){
            currVal += line[i];
            readed = true;
        }
    }
    return i;
}
// satırdaki degerleri okuduktan sonra gereksiz karakter varmı kontrol et
bool CPU::checkEofLine(const string &line){
    for(int i = 0;line[i]!='\0' && line[i]!=';';i++){
        if(line[i]!= ' '){
            return false;
        }
    }
    return true;
}
// string sayı mı diye bak
bool CPU::isNumber(const string &str) 
{
    int i;
/* boş olma durumu                                                            */    
    if(str == "\0")
            return false;
/* negatif olma durumunda bakacağı yerin 0 veya 1 den başlaması               */            
    if(str[0] == '-')
        i = 1;
    else
        i = 0;
    for(;str[i]!='\0';i++)
        if(str[i]< '0' || str[i]>'9')
            return false;
    return true;
}
// string register mı diye bak
bool CPU::isRegister(const string &str) 
{
    int regIndex;
/* 1.indexten itibaren sayıysa sayıya çevir ve register mı diye bak           */
    if(isNumber(&str[1]) == true)
        regIndex = myStrToInt(&str[1]);
    else   
        return false;
    if((str[0] == 'R' || str[0] == 'r') && regIndex >= 1 && regIndex <= NUM_OF_REGS)
        return true;
    return false;
}
// string memory mi diye bak
bool CPU::isMemory(const string &str)
{
    int memIndex;
/* 1.indexten itibaren sayıysa sayıya çevir ve memory adresi mi diye bak      */    
    if(isNumber(&str[1]) == true)
        memIndex = myStrToInt(&str[1]);
    else
        return false;
    if((str[0] == '#') && memIndex >= 0 && memIndex < NUM_OF_MEMS)
        return true;
    return false;
}