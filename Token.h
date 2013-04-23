#pragma once
//Token:20130424
#include <iostream>
#include "String.h"
#include "Kind.h"
#include "SharedPtr.h"
namespace ticket
{
class Token{
public:
	using Ptr = SharedPtr<Token>;
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
}

