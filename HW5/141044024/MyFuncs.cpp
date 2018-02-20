#include <iostream>
#include <fstream>
#include "MyFuncs.h"
using namespace std;

bool commaExist(const string &line)
{
    for(int i=0;line[i] != '\0' && line[i] != ';';i++)
            if(line[i]==',')
                return true;
    return false;
}

int myStrToInt(const string &strNum)
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

string lowToUp(string &str)
{
    for(int i = 0; str[i]!= '\0';i++)
        if(str[i]>='a' && str[i]<='z')
            str[i] -= 'a' - 'A';
    return str;
}