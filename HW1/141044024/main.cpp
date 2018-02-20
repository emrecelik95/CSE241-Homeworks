#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define NUM_OF_REGS 5  // register sayısı

/* dosya adını ve optionu alıp dosyayı okuyup gerekli işlemleri 
   yapan fonksiyonları çağıran fonksiyon                                      */
void readCpuFile(string filename,string option);
/* degeri registera atayan fonksiyon                                          */
bool mov(string reg,int val,int *regs);
/* registarın degerini val kadar artıran fonksiyon                            */
bool add(string reg,int val,int *regs);
/* registarın degerini val kadar azaltan fonksiyon                            */
bool sub(string reg,int val,int *regs);
/* sabiti veya registerın degerini ekrana yazar                               */ 
bool prn(string line,int *regs,string option);
/* dogrudan bir satıra veya registarın 0 olması durumunda satıra atlar        */
bool jmp(string line,int *regs,fstream &theFile,string filename);
/* programı sonlabdırıp registarların son degerini ekrana yazar               */
void hlt(int *regs,string option);
/* verilen line daki register ve value yi bulup pointer olarak döndürür       */
bool getRegAndValue
(string line,string &reg,string &strVal,int *val,int *regs);
/* verilen stringin sayi olup olmadığına bakar                                */
bool isNumber(string strNum);
/* verilen stringin register olup olmadığına bakar                            */
bool isRegister(string reg);
/* option 1 olması durumunda çağrılan ve yapılan instructionu ve 
   registerların durumunu yazar                                               */
void printAll(string ins,string line,int* regs);
/* verilen satırda virgül olup olmadığına bakar                               */
bool commaExist(string line);
/* verilen stringi integera çevirir                                           */
int myStrToInt(string strNum);
/* stringte eğer varsa küçük harfleri büyük harfe çevirir                     */
string lowToUp(string str);

int main(int argc, char**argv) {
/* yanlıs parametre girme durumu                                              */
    if(argc != 3){
        cout << "Invalid parameters!" << endl;
        return 0;
    }
/* option 0-1 dısında bir şey girilirse hata mesajı verir                     */
    if((string)argv[2] != "0" && (string)argv[2] != "1")
    {
        cout << "Option is invalid.It must be 0 or 1 " << endl;
        return 0;
    }
/* dosya okuyup işlemeyi sağlayan fonksiyonu çağırma işlemi                   */
        readCpuFile(argv[1],argv[2]);      
    return 0;
}

void readCpuFile(string filename,string option)
{
/*  dosya okumak için gerekli değişkenleri oluşturma işlemleri                */
    fstream theFile;
    string currIns,currReg = "",valueST = "",restOfLine;
    bool noError = true;
    int registers[NUM_OF_REGS],currVal = 0,i;
/* registerların içeriğini 0 yapma işlemi                                     */    
    for(i=0;i<NUM_OF_REGS;i++)
        registers[i] = 0 ;
/* dosyayı açıp eğer dosya açılırsa program halt edene kadar veya
   hata bulana kadar döngü                                                    */
    theFile.open(filename);
    if(theFile.is_open())
    {
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
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers)){
                    if(isRegister(valueST) == true){
                        currVal = registers[currReg[1] - '0' -1];
                        currReg = valueST;
                        noError = mov(currReg,currVal,registers);
                        }
                    else
                        noError = mov(currReg,currVal,registers);
                    }
                else
                     noError = false;
            }     
            else if(currIns == "ADD")
            {
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers))
                    noError = add(currReg,currVal,registers);
                else
                    noError = false;
            }    
            else if(currIns == "SUB")
            {
                if(getRegAndValue(restOfLine,currReg,valueST,&currVal,registers))
                    noError = sub(currReg,currVal,registers);
                else
                    noError = false;
            }    
            else if(currIns == "JMP")
                noError = jmp(restOfLine,registers,theFile,filename);
            else if(currIns == "PRN"){
                    noError = prn(restOfLine,registers,option);
            }
            else if(currIns == "HLT"){
/* hlt dan sonra noktalı virgül haricinde string veya char olamaz             */            
                for(i=0;restOfLine[i]!='\0' && restOfLine[i]!=';';i++)
                    if(restOfLine[i]!= ' ')
                        noError = false;
                hlt(registers,option);
            }
            else
                noError = false;
/*option un 1 olması durumunda işlemi ve registarlerı her işlemden sonra yazma*/                
            if(option == "1" && currIns != "PRN")
                printAll(currIns,restOfLine,registers);
        }
    }
    else
    {
/* dosya açılmazsa hata mesajı                                                */
        cerr << "File Couldn't Be Opened!" << endl;
    }
/* dosyayı kapat                                                              */    
    theFile.close();
/*  eğer herhangi bir fonksiyon false döndürür ise program halt edip biter    */
    if(noError == false){
        cerr << "'Syntax Error' in the file" << endl;
        hlt(registers,option);
    }
        
    
}

bool mov(string reg,int val,int *regs)
{
/*register numarası - 1 ile indexi bulup indexteki değeri değiştirmek         */
    if(isRegister(reg) == true){
            regs[reg[1] - '0' - 1] = val;
            return true;
    }   
    return false;
}

bool add(string reg,int val,int *regs)
{
/*register numarası - 1 ile indexi bulup indexteki değeri artırmak            */
    if(isRegister(reg) == true){
        regs[reg[1] - '0' - 1] += val; 
        return true;
    }
    return false;
}

bool sub(string reg,int val,int *regs)
{
/*register numarası - 1 ile indexi bulup indexteki değeri azaltmak            */
    if(isRegister(reg) == true){
        regs[reg[1] - '0' - 1] -= val;
        return true;
    }
    return false;
}

void hlt(int *regs,string option)
{
/* option 0 iken registerların son halini yazdır                              */
    if(option == "0"){
        for(int i=0;i < NUM_OF_REGS;i++)
        {
           cout << "R" << i+1 << "=" << regs[i];
           if(i < NUM_OF_REGS - 1 )
               cout << ",";
        }
        cout << endl;
    }
}

bool prn(string line,int *regs,string option)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: 'r 1'   */
    bool readFirst = false,readSpace = false;
    string val = "" ;
    int i;
/* option 1 ise önce işlemi ekrana yazdır                                     */
    if(option == "1")
        printAll("PRN",line,regs);
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
        cout << regs[val[1] - '0' - 1] << endl; 
        return true;
    }
/* degilse sayıysa enrakan bas ve true döndür                                 */    
    else if(isNumber(val) == true){
        cout << val << endl;
        return true;
    }
/* hiçbiri değilse false döndür                                               */    
    return false;
}

bool jmp(string line,int *regs,fstream &theFile,string filename)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: '2 5'   */
    bool readFirst = false,readSpace = false;
/* satıra girme izni için bool degisken                                       */    
    bool goline = false;
    string valueST = "",reg="";
    int value = 0,i;
/* satırda virgül varsa reg ve value degerlerini çek,reg 0 mı diye kontrol et */                
    if(commaExist(line) == true)
    { 
        if(getRegAndValue(line,reg,valueST,&value,regs))   
                goline = (regs[reg[1] - '0' - 1] == 0) ; 
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
(string line,string &reg,string &strVal,int *val,int *regs)
{
/* bu 2 bool degisken yazım hatası(arada bosluk) kontrolü için,örnek: 'R 4'   */
    int i;
    bool readFirst = false,readSpace = false;
/*varsa virgül yoksa satır sonuna kadar ilerle , bosluk olmayanları stringe at*/    
    for(i=0;line[i]!= ',' && line[i]!= '\0';i++)
    {
        if(line[i] != ' '){
            reg += line[i];
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
/* string register ise valın gösterdiği yere registerın degerini ata          */    
    if(isRegister(strVal) == true)
        *val = regs[strVal[1] - '0'  - 1];
/*  string numaraysa stringi integer a çevirip ata                            */        
    else if(isNumber(strVal) == true)
        *val = myStrToInt(strVal);
/* hiçbiri degilse false döndür                                               */        
    else
        return false;
    
    return true;
}

void printAll(string ins,string line,int* regs)
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
    for(i=0;i < NUM_OF_REGS;i++)
    {
       cout << "R" << i+1 << "=" << regs[i];
       if(i < NUM_OF_REGS - 1 )
           cout << ",";
    }
    cout << endl;
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
