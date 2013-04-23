#ifdef COMPILER_UNIT_TEST
#include "Compiler.h"
#include <iostream>

using namespace ticket;

int main(int argc, char* argv[])
{
	Compiler compiler;
	try{
		compiler.StartMainLoop();
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
