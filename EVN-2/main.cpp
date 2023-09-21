#include <iostream>
#include <vector>
#include "complex.h"

int main()
{
	std::vector<complexNumber> array(5);
	array[0] = complexNumber(22,2);
	array[1] = complexNumber(19,9);
	array[2] = complexNumber(6,4);
	array[3] = complexNumber(19,11);
	array[4] = complexNumber(6,7);
	sortArray(array,5);
	for(int i = 0 ; i < 5 ; i++){
		std::cout << array[i] << std::endl;
	}


}

