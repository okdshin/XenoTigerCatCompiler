#pragma once
//Token:20130424
#include <iostream>
#include "String.h"
#include "Kind.h"
#include "SharedPtr.h"
namespace tiger_cat
{
class Token{
public:
	using Ptr = SharedPtr<Token>;
	using Value = String;
	static auto Create(const Kind& kind, const String& value=Value()) -> Ptr {
		return Ptr(new Token(kind, value));	
	}

	auto GetKind()const -> Kind {
		return this->kind;
	}

	auto GetValue()const -> Value {
		return value;
	}
	
private:
	Token(const Kind& kind, const Value& value=String()) 
		: kind(kind), value(value){}
	
	Kind kind;
	Value value;
};
auto operator<<(std::ostream& os, const Token& token) -> std::ostream& {
	os << "Token:" << token.GetKind() << ", " << token.GetValue();
	return os;	
}
}

