#include <iostream>
#include <cmath>

    class complexNumber 
    {
        public:
            int real; 
            int imaginary;
            complexNumber() : real(0), imaginary(0){}
            complexNumber(int real, int imaginary) : real(real), imaginary(imaginary){}
            complexNumber operator + (complexNumber &x);
            complexNumber operator - ( complexNumber &y);
            complexNumber operator * (int constNumber);
            double absolute(){
                 return sqrt(real * real + imaginary * imaginary);
            }
             friend std::ostream& operator<<(std::ostream& out, const complexNumber& num){
                out <<  num.real << "+" << num.imaginary << "i ";
                return out;
            }
    };
    void static sortArray(std::vector<complexNumber> &array, int size ){
                for(int i=0 ; i < size-i ; i++){
                    for(int j=0 ; j< size-i; j++){
                        if(array[j].absolute() > array[j+1].absolute()){
                            std:: swap(array[j], array[j+1]);
                        }
                    }
                }
            }
