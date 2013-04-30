#pragma once
//String:20130424
#include <iostream>
#include <cassert>
#include <vector>
#include "Char.h"

namespace tiger_cat
{
class String{
public:
	using CharVect = std::vector<Char>;

	String(){}
	String(const Char& c){ char_vect.push_back(c); }
	String(const CharVect& char_vect) : char_vect(char_vect){}
	String(const std::string& std_str){
		for(const auto c : std_str){
			char_vect.push_back(Char(c));	
		}	
	}

	static auto GetLine(std::istream& is) -> String {
		std::string std_str;
		std::getline(is, std_str);
		return String(std_str);
	}

	auto At(unsigned int index)const -> Char {
		return char_vect.at(index);
	}

	/*
	auto At(unsigned int index) -> Char& {
		return char_vect.at(index);
		//return *const_cast<Char*>(&At(index));
	}
	*/
	auto Append(const Char& c) -> void {
		char_vect.push_back(c);
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
	str = String(std_str);
	return is;
}

auto operator<<(std::ostream& os, const String& str) -> std::ostream& {
	//os << "String:";
	for(const auto& c : str.char_vect){
		os << c;
	}
	return os;
}

auto operator==(const String& left, const String& right) -> bool {
	if(left.Size() != right.Size()){
		return false;	
	}
	for(unsigned int index = 0; index < left.Size(); ++index){
		if(left.At(index) != right.At(index)){
			return false;	
		}
	}
	return true;
}

auto operator!=(const String& left, const String& right) -> bool {
	return !(left == right);
}
}

