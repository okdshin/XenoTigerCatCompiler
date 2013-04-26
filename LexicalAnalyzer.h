#pragma once
//LexicalAnalyzer:20130416
#include <iostream>
#include "Token.h"

namespace tiger_cat
{

class LexicalAnalyzer{
public:
    LexicalAnalyzer():current_char_index(0), c(){}

	auto Reset(const String& line) -> void {
		current_char_index = 0;
		this->line = line;
		c = GetNextChar();	
	}

	auto GetNextToken() -> Token::Ptr {	
		Token::Ptr token;
		while(true){
			if(!c.IsSpace()){
				break;	
			}
			c = GetNextChar();
		}
		if(c.IsDigit()){
			String value;
			while(true){
				if(!c.IsDigit()){
					token = Token::Create(Kind::IntNumberToken(), value);
					break;
				}
				value.Append(c);
				std::cout << "\tis digit" << std::endl;
				c = GetNextChar();
			}
		}
		else if(c.IsAlpha()){
			String value;
			while(true){
				if(!c.IsAlpha() && !c.IsDigit()){
					token = Token::Create(Kind::VarNameToken(), value);	
					break;
				}
				value.Append(c);
				std::cout << "\tis alpha" << std::endl;
				c = GetNextChar();
			}
		}
		else if(c.IsLeftParen()){
			token = Token::Create(Kind::LeftParenToken());	
			std::cout << "\tis left paren" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsRightParen()){
			token = Token::Create(Kind::RightParenToken());	
			std::cout << "\tis right paren" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsPlus()){
			token = Token::Create(Kind::PlusToken());	
			std::cout << "\tis plus" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsMinus()){
			token = Token::Create(Kind::MinusToken());	
			std::cout << "\tis minus" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsMulti()){
			token = Token::Create(Kind::MultiToken());	
			std::cout << "\tis multi" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsDivi()){
			token = Token::Create(Kind::DiviToken());	
			std::cout << "\tis divi" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsAssign()){
			token = Token::Create(Kind::AssignToken());	
			std::cout << "\tis assign" << std::endl;
			c = GetNextChar();	
		}
		else if(c.IsEol()){
			token = Token::Create(Kind::EolToken());	
			std::cout << "\tis eol" << std::endl;
			c = GetNextChar();		
		}
		std::cout << "NextToken:" << *token << std::endl;
		return token;	
	}

private:
	auto GetNextChar() -> Char {
		if(current_char_index >= line.Size()){
			std::cout << "NextChar:Eol" << std::endl;
			return Char::EolChar();	
		}
		const auto next_char = line.At(current_char_index);
		++current_char_index;
		std::cout << "NextChar:\'" << next_char << "\'" << std::endl;
		return next_char;	
	}

	unsigned int current_char_index;
	String line;
	Char c;
};
}

