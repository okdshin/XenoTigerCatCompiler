#ifdef LEXICALANALYZER_UNIT_TEST
#include "LexicalAnalyzer.h"
#include <iostream>

using namespace tiger_cat;

int main(int argc, char* argv[])
{
	LexicalAnalyzer lexical_analyzer;
	try{
		while(true){
			lexical_analyzer.Reset(String::GetLine(std::cin));
			while(true){
				const auto token = lexical_analyzer.GetNextToken();
				if(token->GetKind() == Kind::EolToken()){
					break;	
				}
			}
		}

	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
