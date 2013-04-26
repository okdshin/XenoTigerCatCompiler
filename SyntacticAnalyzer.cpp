#ifdef SYNTACTICANALYZER_UNIT_TEST
#include "SyntacticAnalyzer.h"
#include <iostream>

using namespace ticket;

int main(int argc, char* argv[])
{
	SyntacticAnalyzer compiler(std::cin);
	try{
		while(true){
			compiler.Statement();
		}
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
