#pragma once
//Calculator:20130416
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <boost/shared_ptr.hpp>

namespace none
{

class Char{
public:
	using RawChar = char;
	explicit Char(RawChar raw_char) : raw_char(raw_char){}
	auto operator==(const Char& c)const -> bool {
		return c.raw_char == raw_char;
	}

	static auto EofChar() -> Char {
		return Char(RawChar('\0'));	
	}

	auto IsSpace()const -> bool {
		return raw_char == RawChar(' ') || raw_char == RawChar('\t');
	}

	auto IsDigit()const -> bool {
		return raw_char == RawChar('0') || 	
			raw_char == RawChar('1') || 	
			raw_char == RawChar('2') || 	
			raw_char == RawChar('3') || 	
			raw_char == RawChar('4') || 	
			raw_char == RawChar('5') || 	
			raw_char == RawChar('6') || 	
			raw_char == RawChar('7') || 	
			raw_char == RawChar('8') || 	
			raw_char == RawChar('9');
	}

	auto IsAlpha()const -> bool {
		return 
			!IsSpace() &&
			!IsDigit() && 
			!IsLeftParen() &&
			!IsRightParen() &&
			!IsPlus() &&
			!IsMinus() &&
			!IsMulti() &&
			!IsDivi() &&
			!IsAssign() &&
			!IsEof();
	}

	auto IsLeftParen()const -> bool {
		return raw_char == RawChar('(');	
	}
	
	auto IsRightParen()const -> bool {
		return raw_char == RawChar(')');	
	}
	
	auto IsPlus()const -> bool {
		return raw_char == RawChar('+');	
	}
	
	auto IsMinus()const -> bool {
		return raw_char == RawChar('-');	
	}
	
	auto IsMulti()const -> bool {
		return raw_char == RawChar('*');	
	}
	
	auto IsDivi()const -> bool {
		return raw_char == RawChar('/');	
	}
	
	auto IsAssign()const -> bool {
		return raw_char == RawChar('=');	
	}
	
	auto IsEof()const -> bool {
		return *this == EofChar();	
	}

	friend auto operator>>(std::istream& is, Char& c) -> std::istream&;
	friend auto operator<<(std::ostream& os, const Char& c) -> std::ostream&;
	
private:
	RawChar raw_char;
};
auto operator>>(std::istream& is, Char& c) -> std::istream& {
	is >> c.raw_char;
	return is;	
}
auto operator<<(std::ostream& os, const Char& c) -> std::ostream& {
	os << c.raw_char;
	return os;	
}

class String{
public:
	using CharVect = std::vector<Char>;

	String(){}
	String(const Char& c){
		char_vect.push_back(c);	
	}
	String(const CharVect& char_vect) : char_vect(char_vect){}

	auto At(unsigned int index) -> Char {
		return char_vect.at(index);
	}

	auto Append(const Char& c) -> void {
		char_vect.push_back(c);
	} 

	auto Clear() -> void {
		char_vect.clear();	
	}

	auto IsEmpty() -> bool {
		return char_vect.size() == 0;	
	}

	auto Size()const -> unsigned int {
		return char_vect.size();	
	}

	friend auto operator>>(std::istream& is, String& str) -> std::istream&;
	friend auto operator<<(std::ostream& os, const String& str) -> std::ostream&;
private:
	CharVect char_vect;
};
auto operator>>(std::istream& is, String& str) -> std::istream& {
	assert(str.char_vect.empty());
	std::basic_string<Char::RawChar> std_str;
	is >> std_str;
	for(const auto c : std_str){
		str.char_vect.push_back(Char(c));	
	}
	return is;
}
auto operator<<(std::ostream& os, const String& str) -> std::ostream& {
	os << "String:";
	for(const auto& c : str.char_vect){
		os << c;
	}
	return os;
}

class Kind{
public:
	static auto IntNumberToken() -> Kind {
		return Kind(kIntNumberToken);	
	}
	
	static auto VarNameToken() -> Kind {
		return Kind(kVarNameToken);	
	}

	static auto LeftParenToken() -> Kind {
		return Kind(kLeftParenToken);	
	}
	
	static auto RightParenToken() -> Kind {
		return Kind(kRightParenToken);	
	}

	static auto PlusToken() -> Kind {
		return Kind(kPlusToken);	
	}

	static auto MinusToken() -> Kind {
		return Kind(kMinusToken);	
	}

	static auto MultiToken() -> Kind {
		return Kind(kMultiToken);	
	}

	static auto DiviToken() -> Kind {
		return Kind(kDiviToken);	
	}

	static auto AssignToken() -> Kind {
		return Kind(kAssignToken);	
	}
	
	static auto EofToken() -> Kind {
		return Kind(kEofToken);	
	}

	bool operator==(const Kind& pair){
		return this->kind_enum == pair.kind_enum;
	}

	friend auto operator<<(std::ostream& os, const Kind& kind) -> std::ostream&;
private:
	enum KindEnum {
		kIntNumberToken, kVarNameToken, 
		kLeftParenToken, kRightParenToken,
		kPlusToken, kMinusToken, kMultiToken, kDiviToken,
		kAssignToken, kEofToken
	};
	Kind(KindEnum kind_enum) : kind_enum(kind_enum){}
	KindEnum kind_enum;
};
auto operator<<(std::ostream& os, const Kind& kind) -> std::ostream& {
	os << "Kind:";
	if(kind.kind_enum == Kind::kEofToken){
		os << "EofToken";	
	}
	else if(kind.kind_enum == Kind::kIntNumberToken){
		os << "IntNumberToken";	
	}
	else if(kind.kind_enum == Kind::kVarNameToken){
		os << "VarNameToken";
	}
	return os;	
}

class Token{
public:
	using Ptr = boost::shared_ptr<Token>;
	static auto Create(const Kind& kind, const String& value=String()) -> Ptr {
		return Ptr(new Token(kind, value));	
	}

	auto GetKind()const -> Kind {
		return this->kind;
	}

	auto GetValue()const -> String {
		return value;
	}
	
private:
	Token(const Kind& kind, const String& value=String()) : kind(kind), value(value){}
	
	Kind kind;
	String value;
};
auto operator<<(std::ostream& os, const Token& token) -> std::ostream& {
	os << "Token:" << token.GetKind() << ", " << token.GetValue();
	return os;	
}


class Calculator{
public:
    Calculator():current_char_index(0){}
    ~Calculator(){}

	auto StartMainLoop() -> void {
		while(true){
			line.Clear();
			std::cin >> line;
			current_char_index = 0;
			while(true){
				const auto token = GetNextToken();
				if(token->GetKind() == Kind::EofToken()){
					break;	
				}
			}
		}
	}

	auto GetNextToken() -> Token::Ptr {	
		Char c = GetNextChar();
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
		else if(c.IsEof()){
			token = Token::Create(Kind::EofToken());	
			std::cout << "\tis eof" << std::endl;
			c = GetNextChar();		
		}
		std::cout << "NextToken:" << *token << std::endl;
		return token;	
	}

	auto GetNextChar() -> Char {
		if(current_char_index >= line.Size()){
			return Char::EofChar();	
		}
		const auto next_char = line.At(current_char_index);
		++current_char_index;
		std::cout << "NextChar:\'" << next_char << "\'" << std::endl;
		return next_char;	
	}

private:
	unsigned int current_char_index;
	String line;
};
}

