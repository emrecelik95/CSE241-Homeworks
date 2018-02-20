#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define NUM_OF_REGS 5  // register sayısı
#define NUM_OF_ADRS 50 // adres sayısı
 
/* dosya adını ve optionu alıp dosyayı okuyup gerekli işlemleri 
   yapan fonksiyonları çağıran fonksiyon                                      */
bool readCpuFile(string filename,string option);
/* degeri registera atayan fonksiyon                                          */
bool mov(string strRef,int val,int *regs,uint8_t *adrs);
/* registarın degerini val kadar artıran fonksiyon                            */
bool add(string strRef,int val,int *regs,uint8_t *adrs);
/* registarın degerini val kadar azaltan fonksiyon                            */
bool sub(string strRef,int val,int *regs,uint8_t *adrs);
/* sabiti veya registerın degerini ekrana yazar                               */ 
bool prn(string line,string option,int *regs,uint8_t *adrs);
/* dogrudan bir satıra veya registarın 0 olması durumunda satıra atlar        */
bool jump(string line,int *regs,uint8_t *adrs,fstream &theFile,string filename,string ins);
/* programı sonlabdırıp registarların son degerini ekrana yazar               */
void hlt(int *regs,uint8_t *adrs,string option);
/* verilen line daki register ve value yi bulup pointer olarak döndürür       */
bool getRegAndValue
(string line,string &firstEl,string &strVal,int *val,int *regs,uint8_t *adrs);
/* verilen stringin sayi olup olmadığına bakar                                */
bool isNumber(string strNum);
/* verilen stringin register olup olmadığına bakar                            */
bool isRegister(string reg);
/* option 1 olması durumunda çağrılan ve yapılan instructionu ve 
   registerların durumunu yazar                                               */
void printAll(string ins,string line,int* regs,uint8_t *adrs,string option);
/* verilen satırda virgül olup olmadığına bakar                               */
bool commaExist(string line);
/* verilen stringi integera çevirir                                           */
int myStrToInt(string strNum);
/* stringte eğer varsa küçük harfleri büyük harfe çevirir                     */
string lowToUp(string str);
/* stringin bir adress olup olmadığını veren fonksiyon                        */
bool isAdress(string adr);
/* registerları ekrana yazan fonksyion                                         */
void printRegs(int *regs);
/* adresleri ekrana yazan fonksiyon                                           */
void printAdrs(uint8_t *adrs);

int main(int argc, char**argv) {
/* yanlıs parametre girme durumu                                              */
    if(argc != 3){
        cout << "Invalid parameters!" << endl;
        return 0;
    }
/* option 0-1 dısında bir şey girilirse hata mesajı verir                     */
    if((string)argv[2] != "0" && (string)argv[2] != "1" && (string)argv[2] != "2")
    {
        cout << "Option is invalid.It must be 0 or 1 or 2" << endl;
        return 0;
    }
/* dosya okuyup işlemeyi sağlayan fonksiyonu çağırma işlemi                   */
    readCpuFile(argv[1],argv[2]);      
    return 0;
}

bool readCpuFile(string filename,string option)
{
/*  dosya okumak için gerekli değişkenleri oluşturma işlemleri                */
    fstream theFile;
    string currIns,currReg = "",valueST = "",restOfLine;
    bool noError = true;
    int registers[NUM_OF_REGS],currVal = 0,i;
    uint8_t adresses[NUM_OF_ADRS];
/* registerların ve adreslerin içeriğini 0 yapma işlemi                       */    
    for(i=0;i<NUM_OF_REGS;i++)
        registers[i] = 0 ;   
    for(i=0;i<NUM_OF_ADRS;i++)
        adresses[i] = 0 ; 
/* dosyayı açıp eğer dosya açılırsa program halt edene kadar veya
   hata bulana kadar döngü                                                    */
    theFile.open(filename);
    if(theFile.is_open())
    {
        i=0;
        while(theFile.eof() == false){
            getline(theFile,restOfLine);
            i++;
        }
        theFile.close();
        if(i>200){
            cout << "Your program can have at most 200 lines.\n";
            return false;
        }
        theFile.open(filename);
        while(currIns != "HLT" && noError == true)
        {   
/* her döngü başında kullanılan stringlerin boşaltılması                      */        
            currReg = "";
            valueST = "";
/* instructionu okuma işlemi ve varsa küçük harfleri büyüğe çevirme işlemi    */            
            theFile >> currIns;    
            currIns = lowToUp(currIns);
/* instruction dan sonra satırın geri kalanını okuma işlemi                   */                                    
            getline(theFile,restOfLine);
/* instruction neyse onun için fonksiyon çağırma ve hata kontrolleri          */  
/*(noError) hata durumunu tuttuğu için fonksiyonların döndürdüğü değeri tutar */          
            if(currIns == "MOV")
            {
/* mov da özel durum : eğer mov r1,r2 ise r1 i r2 ye ata durumu için kontrol  */             
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers,adresses)){
                    if(isRegister(valueST) == true || isAdress(valueST) == true){
                        if(isRegister(currReg) == true)
                            currVal = (registers[myStrToInt(&currReg[1]) - 1]);
                        else if(isAdress(currReg) == true)
                            currVal = (adresses[myStrToInt(&currReg[1])]);
                        currReg = valueST;
                    }
                    noError = mov(currReg,currVal,registers,adresses);
                }
                else
                    noError = false;
            }     
            else if(currIns == "ADD")
            {
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers,adresses))   
                    noError = add(currReg,currVal,registers,adresses);
                else
                    noError = false;
            }    
            else if(currIns == "SUB")
            {
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers,adresses))   
                    noError = sub(currReg,currVal,registers,adresses);
                else
                    noError = false;
            }    
            else if(currIns == "JMP" || currIns == "JPN")
                noError = jump(restOfLine,registers,adresses,theFile,filename,currIns);
            else if(currIns == "PRN"){
                    noError = prn(restOfLine,option,registers,adresses);
            }
            else if(currIns == "HLT"){
/* hlt dan sonra noktalı virgül haricinde string veya char olamaz             */            
                for(i=0;restOfLine[i]!='\0' && restOfLine[i]!=';';i++)
                    if(restOfLine[i]!= ' ')
                        noError = false;
                hlt(registers,adresses,option);
            }
            else
                noError = false;
/*option un 1 olması durumunda işlemi ve registarlerı her işlemden sonra yazma*/                
            if(option != "0" && currIns != "PRN")
                printAll(currIns,restOfLine,registers,adresses,option);
        }
    }
    else
    {
/* dosya açılmazsa hata mesajı                                                */
        cerr << "File Couldn't Be Opened!" << endl;
        return false;
    }
/* dosyayı kapat                                                              */    
    theFile.close();
/*  eğer herhangi bir fonksiyon false döndürür ise program halt edip biter    */
    if(noError == false){
        cerr << "'Syntax Error' in the file" << endl;
        hlt(registers,adresses,option);
        return false;
    }
        
    return true;
}

bool mov(string strRef,int val,int *regs,uint8_t *adrs)
{
/*adress veya register'a göre arraylerin indexine ulaşıp deger atama          */
    if(isRegister(strRef) == true){
        regs[myStrToInt(&strRef[1]) - 1] = val;
        return true;
    } 
    else if(isAdress(strRef) == true){
        if(val < 0){
/*          memory negatif sayı tutamaz                                       */
            cout << "Memory can't have negatif numbers\n";
            return false;
        }
        adrs[myStrToInt(&strRef[1])] = val;
        return true;
    }
    return false;
}

bool add(string strRef,int val,int *regs,uint8_t *adrs)
{
/*adress veya register'a göre arraylerin indexine ulaşıp degeri artırma       */
    if(isRegister(strRef) == true){
        regs[myStrToInt(&strRef[1]) - 1] += val;
        return true;
    } 
    else if(isAdress(strRef) == true){
        cout << "Addition and Subtraction is not available for memory\n"; 
        return false;
    }
    return false;
}

bool sub(string strRef,int val,int *regs,uint8_t *adrs)
{
/*adress veya register'a göre arraylerin indexine ulaşıp degeri azaltma       */
    if(isRegister(strRef) == true){
        regs[myStrToInt(&strRef[1]) - 1] -= val;
        return true;
    } 
    else if(isAdress(strRef) == true){
        cout << "Addition and subtraction is not available for memory\n"; 
        return false;
    }
    return false;
}

void hlt(int *regs,uint8_t *adrs,string option)
{
/* option 0 iken registerların ve memory nin son halini yazdır                */
    if(option == "0"){
        printRegs(regs);
        cout << endl;
        printAdrs(adrs);
        cout << endl;
    }
}

bool prn(string line,string option,int *regs,uint8_t *adrs)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: 'r 1'   */
    bool readFirst = false,readSpace = false;
    string val = "" ;
    int i;
/* option 1 ise önce işlemi ekrana yazdır                                     */
    if(option == "1" || option == "2")
        printAll("PRN",line,regs,adrs,option);
/* boşluk olmayan herşeyi okuyup strine at,eğer ilk chardan(boşluk olmayan)sonra 
bosluk okursa ve daha sonra üzerine bir char daha okumak isterse false döndür */
    for(i=0;line[i] != '\0' && line[i] != ';';i++)
    {
        if(line[i]!= ' '){
            val += line[i];
            readFirst = true;
            if(readSpace == true)
                return false;
        }
        if(readFirst == true && line[i] == ' ')
            readSpace = true;
    }
/* registersa ekrana bas ve true döndür                                       */    
    if(isRegister(val)){
        cout << regs[myStrToInt(&val[1]) - 1] << endl; 
        return true;
    }
/* degilse sayıysa ekrana bas ve true döndür                                  */    
    else if(isNumber(val) == true){
        cout << val << endl;
        return true;
    }
/* degilse adresse memory deki degeri ekrana bas ve true döndür               */    
    else if(isAdress(val)){
        cout << unsigned(adrs[myStrToInt(&val[1])]) << endl; 
        return true;
    }
/* hiçbiri değilse false döndür                                               */    
    return false;
}

bool jump(string line,int *regs,uint8_t *adrs,fstream &theFile,string filename,string ins)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: '2 5'   */
    bool readFirst = false,readSpace = false;
/* satıra girme izni için bool degisken                                       */    
    bool goline = false;
    string valueST = "",strRef="";
    int value = 0,i;
/*satırda virgül varsa reg/adres ve value degerlerini çek,0 mı diye kontrol et*/                
    if(commaExist(line) == true)
    { 
        if(getRegAndValue(line,strRef,valueST,&value,regs,adrs)){
            if(isRegister(strRef) == true){
                if(ins == "JMP")
                    goline = (regs[strRef[1] - '0' - 1] == 0) ; 
                else if(ins == "JPN")
                    goline = (regs[strRef[1] - '0' - 1] <= 0) ; 
            }
            else if(isAdress(strRef) == true){
                if(ins == "JMP")
                    goline = (adrs[myStrToInt(&strRef[1])] == 0) ;
                else if(ins == "JPN")
                    goline = (adrs[myStrToInt(&strRef[1])] <= 0) ;
            }
                
        }
        else
                return false;
    }
    else
    {
/*  virgül yoksa gideceği satırın numarasını al                               */   
        goline = true;
        for(i = 0;line[i]!= '\0' && line[i]!= ';';i++)
        {
            if(line[i]!= ' '){
                valueST += line[i];
                readFirst = true;
            if(readSpace == true)
                return false;
            }
            if(readFirst == true && line[i] == ' ')
                readSpace = true;
        }    
/* alınan deger sayı degilse false döndür , sayıysa string sayıyı int e döndür*/        
        if(isNumber(valueST) == false)
            return false;
        value = myStrToInt(valueST);
    }
/*satıra gitme izni varsa dosyayı kapat aç(en başa git) ve deger kadar line oku*/    
    if(goline)
    {
        theFile.close();
        theFile.open(filename);
        for(i=1;i< value ;i++)
            getline(theFile,line);
    } 
/* syntax hatası bulamadıysa true döndürsün                                   */    
    return true;
}

bool getRegAndValue
(string line,string &firstEl,string &strVal,int *val,int *regs,uint8_t *adrs)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: 'R 4'   */
    int i;
    bool readFirst = false,readSpace = false;
/*varsa virgül yoksa satır sonuna kadar ilerle , bosluk olmayanları stringe at*/    
    for(i=0;line[i]!= ',' && line[i]!= '\0';i++)
    {
        if(line[i] != ' '){
            firstEl += line[i];
            readFirst = true;
            if(readSpace == true)
                return false;
        }
        if(readFirst == true && line[i] == ' ')
            readSpace = true;
        
    }
/* virgül yoksa sona gelmiştir false döndürür                                 */    
    if(line[i] == '\0')
        return false;
/* hata için gerekli bool degiskenleri bir sonraki okuma için sıfırlama       */        
    readFirst = false;
    readSpace = false;
/* virgülden bir sonraki indexten başla sona veya noktalı virgüle kadar git
   okuduğunu stringe at                                                       */    
    for(i = i+1 ;line[i] != '\0' && line[i] != ';';i++)
    {
        if(line[i] != ' '){
            strVal += line[i];
            readFirst = true;
            if(readSpace == true)
                return false;
        }
        if(readFirst == true && line[i] == ' ')
            readSpace = true;
    }
/* stringte eğer varsa küçük harfleri büyük harfe çevir                       */    
    strVal = lowToUp(strVal);
/* string register ise val'ın gösterdiği yere registerın degerini ata         */    
    if(isRegister(strVal) == true)
        *val = regs[myStrToInt(&strVal[1]) - 1];
/* string adress ise val'ın gösterdiği yere adressin tuttuğu degeri ata       */    
    else if(isAdress(strVal) == true)
        *val = adrs[myStrToInt(&strVal[1])];
/*  string numaraysa stringi integer a çevirip ata                            */        
    else if(isNumber(strVal) == true)
        *val = myStrToInt(strVal);
/* hiçbiri degilse false döndür                                               */        
    else
        return false;
    
    return true;
}

void printAll(string ins,string line,int* regs,uint8_t *adrs,string option)
{
    int i;
/* instructiona göre format hazırlayıp yapılan işlem - registerlar ve 
   içeriklerini ekrana bastır                                                 */    
    cout << ins << " ";
    if(ins == "MOV" || ins == "SUB" || ins == "ADD" || 
      (ins == "JMP" && commaExist(line) == true))
    {
        for(i = 0;line[i]!=',';i++)
            if(line[i] != ' ')
                cout << line[i];
        cout << " , ";
        for(i = i +1;line[i]!= ';' && line[i]!= '\0';i++)
            if(line[i] != ' ')
                cout << line[i];
        cout << "  -  ";
    }
    else if(ins == "PRN" || (ins == "JMP" && commaExist(line) == false))
    {
        for(i = 0;line[i]!= ';' && line[i]!= '\0';i++)
            if(line[i] != ' ')
                cout << line[i]; 
        cout << "       -  ";      
    }
    else if(ins == "HLT")
        cout << "        -  ";
    if(option == "1" || option == "2")
        printRegs(regs);
    cout << endl;
    if(option == "2"){
        printAdrs(adrs);
        cout << endl;
    }
        
}
bool commaExist(string line)
{
    for(int i=0;line[i] != '\0' && line[i] != ';';i++)
            if(line[i]==',')
                return true;
    return false;
}

bool isNumber(string strNum)
{
    int i;
/* boş olma durumu                                                            */    
    if(strNum == "\0")
            return false;
/* negatif olma durumunda bakacağı yerin 0 veya 1 den başlaması               */            
    if(strNum[0] == '-')
        i = 1;
    else
        i = 0;
    for(;strNum[i]!='\0';i++)
        if(strNum[i]< '0' || strNum[i]>'9')
            return false;
    return true;
}

bool isRegister(string reg)
{
    int regNum;
/* 1.indexten itibaren sayıysa sayıya çevir ve register mı diye bak           */
    if(isNumber(&reg[1]) == true)
        regNum = myStrToInt(&reg[1]);
    if((reg[0] == 'R' || reg[0] == 'r') && regNum >= 1 && regNum <= NUM_OF_REGS)
        return true;
    return false;
}

bool isAdress(string adr)
{
    int adrNum;
/* 1.indexten itibaren sayıysa sayıya çevir ve adresregisters mı diye bak             */    
    if(isNumber(&adr[1]) == true)
        adrNum = myStrToInt(&adr[1]);
    if((adr[0] == '#') && adrNum >= 0 && adrNum < NUM_OF_ADRS)
        return true;
    return false;
}

int myStrToInt(string strNum)
{
    int digit,i,j,number = 0,mult;
/* basamak sayısını bul                                                       */    
    for(digit = 0;strNum[digit] != '\0';digit++);
/* stringi parçala adım adım integera çevir                                   */
    for(i=0 ; i < digit ; i++)
    {
        mult = 1;
        for(j=0;j<i;j++)
            mult *= 10;  
        number += (strNum[digit - i - 1] - '0') * mult; 
    }
    return number;
}

string lowToUp(string str)
{
    for(int i = 0; str[i]!= '\0';i++)
        if(str[i]>='a' && str[i]<='z')
            str[i] -= 'a' - 'A';
    return str;
}

void printRegs(int *regs)
{
    for(int i=0;i < NUM_OF_REGS;i++)
    {
       cout << "R" << i+1 << "=" << regs[i];
       if(i < NUM_OF_REGS - 1 )
           cout << ",";
    }
}
void printAdrs(uint8_t *adrs)
{
    for(int i=0;i < NUM_OF_ADRS;i++)
    {
        cout << "#" << i << " = " << unsigned(adrs[i]) << " ";
        if(i < NUM_OF_ADRS - 1 )
            cout << " , ";
        if(i % 10 == 0 && i != 0)
            cout << endl;
    }    
}
