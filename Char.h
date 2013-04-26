#pragma once
//Char:20130424
#include <iostream>

namespace tiger_cat
{
class Char{
public:
	using RawChar = char;

	Char(){}
	explicit Char(RawChar raw_char) : raw_char(raw_char){}
	
	auto operator==(const Char& c)const -> bool {
		return c.raw_char == raw_char;
	}

	static auto EolChar() -> Char {
		return Char(RawChar('\0'));	
	}

	auto IsLeftParen()const -> bool { return raw_char == RawChar('('); }
	auto IsRightParen()const -> bool { return raw_char == RawChar(')'); }
	auto IsPlus()const -> bool { return raw_char == RawChar('+'); }
	auto IsMinus()const -> bool { return raw_char == RawChar('-'); }
	auto IsMulti()const -> bool { return raw_char == RawChar('*'); }
	auto IsDivi()const -> bool { return raw_char == RawChar('/'); }
	auto IsAssign()const -> bool { return raw_char == RawChar('='); }
	auto IsEol()const -> bool { return *this == EolChar(); }

	auto IsSpace()const -> bool {
		return raw_char == RawChar(' ') || raw_char == RawChar('\t');
	}

	auto IsDigit()const -> bool {
		return 
			raw_char == RawChar('0') || raw_char == RawChar('1') || 	
			raw_char == RawChar('2') || raw_char == RawChar('3') || 	
			raw_char == RawChar('4') || raw_char == RawChar('5') ||
			raw_char == RawChar('6') || raw_char == RawChar('7') || 	
			raw_char == RawChar('8') || raw_char == RawChar('9');
	}

	auto IsAlpha()const -> bool {
		return 
			!IsSpace() && !IsDigit() && 
			!IsLeftParen() && !IsRightParen() &&
			!IsPlus() && !IsMinus() && !IsMulti() && !IsDivi() &&
			!IsAssign() && !IsEol();
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
}

