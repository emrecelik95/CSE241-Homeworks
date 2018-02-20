#include <iostream>
#include <fstream>

#include "BigramDyn.h"
#include "MyException.h"

// datatipini,capaciteyi ve used u default ilklendir
template<class T>
BigramDyn<T>::BigramDyn():dataType(1),capacity(10),used(0) {
    arr = new T[capacity]; // dynamic array için capacity kadar yer al
}

// datatipini,capactiteyi ve used u ilklendir
template<class T>
BigramDyn<T>::BigramDyn(const int& type):dataType(type),capacity(10),used(0){
    arr = new T[capacity]; // dynamic array için capacity kadar yer al
}

// diğerinin member variable larını buna ata
template<class T>
BigramDyn<T>::BigramDyn(const BigramDyn& other):dataType(other.dataType),
                               capacity(other.capacity),used(other.used) {
    // capacity kadar yer al (template)
    arr = new T[capacity];
    for(int i = 0;i < getUsed();++i) // içini diğerinin elemanlarıyla doldur
        arr[i] = other.arr[i];
}

template<class T>
BigramDyn<T>::~BigramDyn() { // destructorda template pointer'ı yok et
    delete [] arr;
}

template<class T>
BigramDyn<T>& BigramDyn<T>::operator =(const BigramDyn& other){
    
    // kapasiteler aynı değilse diziyi silip diğerininki kadar yer al
    if(getCapacity() != other.getCapacity()){
        delete [] arr;
        arr = new T[other.getCapacity()];
    }
   
    // diğerinin member variable larını buna ata
    setDataType(other.getDataType());
    setCapacity(other.getCapacity());
    setUsed(other.getUsed());
    // yeni kapasite kadar yer al
    arr = new T[getCapacity()];
    for(int i = 0;i < getUsed();++i) // digerinin dizisini buna at
        arr[i] = other.arr[i];
    
    return *this;
}

template<class T>
void BigramDyn<T>::readFile(const string& filename)throw(MyException){
    fstream file;
    T temp;
    file.open(filename);
    if(!file.is_open()) // dosya açılmazsa exception fırlat
        throw MyException("File couldn't be opened!");
    
    if(!(file >> temp)){ // dosya boşmu kontrolu
        throw MyException("File is in wrong format!");
    }
    
    file.close();
    file.open(filename);  
    
    while(!file.eof()){
        if((file >> temp)){  // dosyadaki tip istenen tipte değilse exception fırlat
            if(getUsed() >= getCapacity()){ // arrayi dolduruyorken kapasiteye ulasmışsa
                setCapacity(2 * getCapacity() + 1); // kapasiteyi arttır
                T* temp = new T[getCapacity()]; // yeni kapasite kadar yer al
                for(int i = 0;i < getUsed();++i) // arrayi tempe kopyala
                    temp[i] = arr[i];
                
                delete [] arr; // arrayi yok et
                arr = temp;    // sonra tempi arraya at
            }
            arr[getUsed()] = temp;       // ekleme işlemi(used yani sıradaki indise degeri koy)
            setUsed(used + 1);           // sonrasında used'ı 1 arrttır
        }    
        else if(!file.eof())  // file.eof bi tane fazla okudugundan içerde kontrol gerekli
            throw MyException("File is not in the correct format!");

    }
}

template<class T>
int BigramDyn<T>::numGrams()const{ // used(yani size) - 1 dondur
    return getUsed() - 1;
}

// dizideki ikililer bigram 1 ve bigram 2 mi? öyleyse sayacı arttır
template<class T>
int BigramDyn<T>::numOfGrams(const T& bigram1, const T& bigram2) {
    int count = 0;
    for(int i = 0;i < numGrams();++i)
        if(arr[i] == bigram1 && arr[i + 1] == bigram2)
            ++count;

    return count;
}


template<class T>
const pair<T,T> BigramDyn<T>::maxGrams() {
    int max = 0,current;
    pair<T,T> tmpPair; // return degeri
    for(int i = 0;i < numGrams();++i){
        current = numOfGrams(arr[i],arr[i + 1]); // aktif ikilinin tekrar sayısı
        if(current >  max){ // max dan büyükse pairi bu çiftten yap , current'i max'a ata
            max = current;
            tmpPair.first = arr[i];
            tmpPair.second = arr[i + 1];
        }
    }
    return tmpPair;
}

template<class T>
ostream& BigramDyn<T>::print(ostream& os){
// ikilileri karşılaştırıp yerlerini değiştirmek için pair arrayi
    pair<T,T>* bigs = new pair<T,T>[numGrams()]; // numgrams() ın degeri kadar yer al
    bool sameExist;
    
    for(int i = 0 ; i < numGrams() ; ++i){ // mapteki ikilileri paire doldur
        bigs[i].first = arr[i];
        bigs[i].second = arr[i + 1];
    }
    for(int i = 0 ; i < numGrams() ; ++i) // dıs dongu indisi karsılastırılacak pair
        for(int j = i + 1 ; j < numGrams() - 1; ++j)
            // iç dongude ise diğer her bir pairle karşılaştırma yapılır
            if(numOfGrams(bigs[i].first,bigs[i].second) < numOfGrams(bigs[j].first,bigs[j].second))
                bigs[i].swap(bigs[j]);  // iki ikiliyi swap et
    
    // tekrar sayısına gore büyükten küçüğe dogru ikilileri ve tekrar sayılarını
    // os a aktar ve os u return et
    for(int i = 0 ; i < numGrams() ; ++i) // her pairi 1 defa bastırmak için gerekli
    {
        sameExist = false;                // kendisi mi ?
        for(int j = i - 1; j >= 0 ; --j)  // aynı pairi gorurse bi daha yazmasın
        {
            if(bigs[i].first == bigs[j].first && bigs[i].second == bigs[j].second)
            {
                sameExist = true;  
                j = -1;    
            }
        }
        if(!sameExist)  // kendisinden daha once ekrana yazılmadıysa yazsın
            os << bigs[i].first << " " << bigs[i].second << " : " 
               << numOfGrams(bigs[i].first,bigs[i].second) << " times " << endl;
    }
    return os;
}

template<class T>
const int& BigramDyn<T>::getDataType() const{
    return dataType;
}

template<class T>
void BigramDyn<T>::setDataType(const int& value){
    dataType = value;
}

template<class T>
const int& BigramDyn<T>::getCapacity() const{
    return capacity;
}

template<class T>
void BigramDyn<T>::setCapacity(const int& value){
    capacity = value;
}

template<class T>
const int& BigramDyn<T>::getUsed() const{
    return used;
}

template<class T>
void BigramDyn<T>::setUsed(const int& value){
    used = value;
}
