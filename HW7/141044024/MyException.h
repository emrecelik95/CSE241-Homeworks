#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

// exception dan miras al
class MyException : public exception {
public:
    MyException(const char* msg); // parametre olarak mesaj al
    virtual const char* what() const throw() override; // exceptiondaki what'ın ovveride edilmesi
private:
    const char* message; // parametre olarak gelecek olan const char* hata mesajı
};

#endif /* MYEXCEPTION_H */

