#pragma once
//String:20130424
#include <iostream>
#include <cassert>
#include <vector>
#include "Char.h"

namespace ticket
{
class String{
public:
	using CharVect = std::vector<Char>;

	String(){}
	String(const Char& c){ char_vect.push_back(c); }
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
}

