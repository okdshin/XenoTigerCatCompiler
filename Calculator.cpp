#ifdef CALCULATOR_UNIT_TEST
#include "Calculator.h"
#include <iostream>

using namespace none;

int main(int argc, char* argv[])
{
	Calculator calculator;
	try{
		calculator.StartMainLoop();
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
