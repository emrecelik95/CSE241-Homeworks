#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include "Bigram.h"
#include "MyException.h" // exception clas ım

using namespace std;

template<class T> // class ın template olması gerekiyor
class BigramDyn : public Bigram<T>{
public:
    BigramDyn();
    BigramDyn(const int& type);
    BigramDyn(const BigramDyn& other);
    BigramDyn<T>& operator=(const BigramDyn& other);
    virtual ~BigramDyn();
    // virtual tüm fonksiyonlar override edildi
    virtual void readFile(const string& filename)throw(MyException)override;
    virtual int numGrams()const override;
    virtual int numOfGrams(const T& bigram1,const T& bigram2) override;
    virtual const pair<T,T> maxGrams() override;
    virtual ostream& print(ostream& os)override;
    // getter setter'lar
    const int& getDataType()const;
    void setDataType(const int& value);
    const int& getCapacity()const;
    void setCapacity(const int& value);
    const int& getUsed()const;
    void setUsed(const int& value);
private:
    int dataType;
    T* arr;
    int capacity;
    int used;
};

#endif

