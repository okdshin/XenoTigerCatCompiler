#pragma once
//Compiler:20130416
#include <iostream>
#include "Token.h"

namespace tiger_cat
{

class Compiler{
public:
    Compiler():current_char_index(0), c(){}

	auto StartMainLoop() -> void {
		while(true){
			current_char_index = 0;
			line = String::GetLine(std::cin);
			c = GetNextChar();
			while(true){
				const auto token = GetNextToken();
				if(token->GetKind() == Kind::EolToken()){
					break;	
				}
			}
		}
	}


private:
	LexicalAnalyzer lexical_analyzer;
};
}

