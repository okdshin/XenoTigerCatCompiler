#pragma once
//Kind:20130424
#include <iostream>

namespace tiger_cat
{
class Kind{
public:
	static auto IntNumberToken() -> Kind 	{ return Kind("IntNumberToken"); }
	static auto VarNameToken() -> Kind 		{ return Kind("VarNameToken"); }
	static auto LeftParenToken() -> Kind 	{ return Kind("LeftParenToken"); }
	static auto RightParenToken() -> Kind 	{ return Kind("RightParenToken");	}
	static auto PlusToken() -> Kind 		{ return Kind("PlusToken"); }
	static auto MinusToken() -> Kind 		{ return Kind("MinusToken"); }
	static auto MultiToken() -> Kind 		{ return Kind("MultiToken"); }
	static auto DiviToken() -> Kind 		{ return Kind("DiviToken");	}
	static auto AssignToken() -> Kind 		{ return Kind("AssignToken");	}
	static auto EolToken() -> Kind 			{ return Kind("EolToken"); }

	bool operator==(const Kind& pair){ return this->kind_str == pair.kind_str; }

	friend auto operator<<(std::ostream& os, const Kind& kind) -> std::ostream&;

private:
	Kind(const std::string& kind_str) : kind_str(kind_str){}
	std::string kind_str;
};
auto operator<<(std::ostream& os, const Kind& kind) -> std::ostream& {
	os << "Kind:" << kind.kind_str;	
	return os;	
}
}

