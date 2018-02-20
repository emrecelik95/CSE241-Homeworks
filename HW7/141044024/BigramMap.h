#ifndef BIAGRAMMAP_H
#define BIAGRAMMAP_H

#include <map>
#include <vector>
#include "Bigram.h"
#include "MyException.h" // kendi yazdığım exception clası

template<class T>   // class ın template olması gerekiyor
class BigramMap : public Bigram<T>{
public:
    BigramMap();
    BigramMap(int type);   
    virtual ~BigramMap();
    // virtual tüm fonksiyonlar override edildi
    virtual void readFile(const string& filename)throw(MyException)override;
    virtual int numGrams()const override;
    virtual int numOfGrams(const T& bigram1,const T& bigram2) override;
    virtual const pair<T,T> maxGrams() override;
    virtual ostream& print(ostream& os)override;

private:
    int dataType;      // parametre olarak gelen data tipi
    map<int,T> mapObj; // key i integer olan ve template deger tutan map
};

#endif 

