#include <fstream>

#include "BigramMap.h"

// birşey girilmezse default olarak data tipi 1 olsun
template<class T>
BigramMap<T>::BigramMap():dataType(1){}

// datatipini ilklendir
template<class T>
BigramMap<T>::BigramMap(int type):dataType(type){}

template<class T>
BigramMap<T>::~BigramMap() {}


template<class T>
void BigramMap<T>::readFile(const string& filename)throw(MyException){
    fstream file;
    T temp;
    int index = 0;
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
            mapObj[index] = temp; // sorun yoksa mapi doldur
            ++index;     
        }    
        else if(!file.eof())  // file.eof bi tane fazla okudugundan içerde kontrol gerekli
            throw MyException("File is not in the correct format!");        
           
    }
    

}

template<class T>
int BigramMap<T>::numGrams()const{ // toplam bigrams sayısı = size - 1
    if(mapObj.size() == 0)         // map boşsa -1 dondurmesin 0 dondursun
        return 0;
    
    return mapObj.size() - 1;
}

template<class T>
int BigramMap<T>::numOfGrams(const T& bigram1, const T& bigram2) {
    int count = 0;
    for(int i = 0;i < numGrams();++i)
        if(mapObj[i] == bigram1 && mapObj[i + 1] == bigram2) // ardışıklar t1,t2 mi?
            ++count;                                         // sayacı arttır

    return count;
}

template<class T>
const pair<T,T> BigramMap<T>::maxGrams() {
    int max = 0,current;
    pair<T,T> tmpPair; // return degeri
    for(int i = 0;i < numGrams();++i){
        current = numOfGrams(mapObj[i],mapObj[i + 1]); // aktif ikilinin tekrar sayısı
        if(current >  max){ // max dan büyükse pairi bu çiftten yap , current'i max'a ata
            max = current;
            tmpPair.first = mapObj[i];
            tmpPair.second = mapObj[i + 1];
        }
    }
    return tmpPair;
}

template<class T>
ostream& BigramMap<T>::print(ostream& os){
    // ikilileri karşılaştırıp yerlerini değiştirmek için pair arrayi
    pair<T,T>* bigs = new pair<T,T>[numGrams()]; // numgrams() ın degeri kadar yer al
    bool sameExist;
    
    for(int i = 0 ; i < numGrams() ; ++i){ // mapteki ikilileri paire doldur
        bigs[i].first = mapObj[i];
        bigs[i].second = mapObj[i + 1];
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
