#include <iostream>
#include <fstream>
#include "CPUProgram.h"

using namespace std;

CPUProgram ::CPUProgram(const string &filename){
    readFile(filename);
}

bool CPUProgram::readFile(const string &filename){
    fstream theFile;
    int i = 0;
    string line;
    theFile.open(filename);
    if(!theFile.is_open()){
        cerr << "File Couldn't be opened\n";
        return false;
    }
    while(!theFile.eof()){ // satırları lines'a teker teker at
        getline(theFile,line);
        lines.push_back(line);
        i++;
    }
    numOfLines = i - 1;   // size ı ata
    theFile.close();
    return true;
}

int CPUProgram::size(){ 
    return numOfLines;            // size ı return et
}

string CPUProgram::getLine(const int &lineNum){
    return lines[lineNum - 1];    //verilen numaradaki satırı dondur
}