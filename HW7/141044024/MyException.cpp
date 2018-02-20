#include "MyException.h"

MyException::MyException(const char* msg):message(msg){} // mesageyi ilklendir

const char* MyException::what() const throw(){ // hata mesajını return et
    return message;
}
