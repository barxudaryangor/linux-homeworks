#include <iostream>
#include <vector>
#include "complex.h"
    complexNumber complexNumber::operator+ (complexNumber &x){
      return complexNumber(real+x.real, imaginary+x.imaginary);
    }
    complexNumber complexNumber:: operator- (complexNumber &y){
         return complexNumber(real+y.real, imaginary+y.imaginary);
    }
    complexNumber complexNumber:: operator* (int constNumber){
        return complexNumber(constNumber * real, constNumber * imaginary);
    }
