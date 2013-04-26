#pragma once
//SyntacticAnalyzer:20130416
#include <iostream>
#include "LexicalAnalyzer.h"

namespace ticket
{

class SyntacticAnalyzer{
public:
    SyntacticAnalyzer(std::istream& is):is(is){}

	auto Statement() -> void {
		lexical_analyzer.Reset(String::GetLine(is));
		while(1){
			auto token = lexical_analyzer.GetNextToken();
			std::cout << *token << std::endl;
			if(token->GetKind() == Kind::EolToken()){
				break;	
			}
			if(token->GetKind() == Kind::VarNameToken()){
					
			}
		}
		
	}

	auto Expression() -> void {
		
	}

	auto Factor() -> void {
		
	}


private:
	std::istream& is;
	LexicalAnalyzer lexical_analyzer;
};
}

