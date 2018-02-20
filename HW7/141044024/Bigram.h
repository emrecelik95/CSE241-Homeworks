#ifndef BIGRAM_H
#define BIGRAM_H

#include <iostream>
#include <exception>
using namespace std;

// Bigram abstract class,fonksiyonları pure virtual.
// Template olması gerekiyor.
template<class T>
class Bigram {
public:
    Bigram(){};
    virtual ~Bigram(){};
    // dosyaı adı alıp dosya okuyup mapi dolduran fonk veya exception fırlatan fonk
    virtual void readFile(const string& filename)throw(exception) = 0;
    // total bigram sayısını return eder
    virtual int numGrams()const = 0;
    // 2 bigrams alır ve ve bu bigramın tekrar sayısını return eder
    virtual int numOfGrams(const T& bigram1,const T& bigram2) = 0;
    // en çok tekrar eden bigramı pair olarak return eder
    virtual const pair<T,T> maxGrams() = 0;
    // friend fonksiyon inherit edilmediği için virtual değil ve virtual olan fonksiyonu dondurur(inline)
    friend ostream& operator<< (ostream& os,Bigram<T>& bigram){return bigram.print(os);}
    // ostream alıp degistirip return eder
    virtual ostream& print(ostream& os) = 0;
};


#endif