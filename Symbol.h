#pragma once
//Symbol:20130425
#include <iostream>
#include <boost/format.hpp>
#include "SharedPtr.h"
#include "String.h"

namespace tiger_cat
{

class Int {
public:
	Int(int value) : value(value){}
	static auto Size() -> unsigned int { return 4; }
	auto GetValue() -> int {
		return value;
	}
private:
	int value;

};

class Symbol {
public:
	using Ptr = SharedPtr<Symbol>;
	using Name = String;
	
	class Kind {
	public:
		Kind(const std::string& kind_str):kind_str(kind_str){}
		static auto Var() -> Kind { return Kind("Var");	}
		static auto Func() -> Kind { return Kind("Func"); }

		auto operator==(const Kind& kind) -> bool {
			return this->kind_str == kind.kind_str;
		}
		
		friend auto operator<<(std::ostream& os, const Kind& kind) -> std::ostream&;
	private:
		std::string kind_str;
	};

	class Type {
	public:
		Type(const std::string& type_str) : type_str(type_str){}
		static auto Int() -> Type { return Type("Int");	}
		static auto Void() -> Type { return Type("Void"); }

		auto operator==(const Type& type) -> bool {
			return this->type_str == type.type_str;
		}
		
		friend auto operator<<(std::ostream& os, const Type& type) -> std::ostream&;
	private:
		std::string type_str;
	};

	static auto Create(
			const Name& name, const Kind& kind, const Type& type) -> Ptr {
		return Ptr(new Symbol(name, kind, type));	
	}

	auto GetName()const -> Name {
		return name;	
	}

	auto AsInt() -> Int {
		assert(kind == Kind::Var() && type == Type::Int());
		assert(byte_vect.size() == Int::Size());
		int value = 
			static_cast<int>(byte_vect[0])+
			(static_cast<int>(byte_vect[1])<<8)+
			(static_cast<int>(byte_vect[2])<<16)+
			(static_cast<int>(byte_vect[3])<<24);
		return Int(value);
	}

	friend auto operator<<(
			std::ostream& os, const Symbol& symbol) -> std::ostream& {
		os << boost::format("{Symbol:(Name:\"%1%\", Kind:\"%2%\", Type:\"%3%\")}")
			% symbol.name
			% symbol.kind
			% symbol.type;
		return os;
	}
private:
	Symbol(const Name& name, const Kind& kind, const Type& type) 
		: name(name), kind(kind), type(type){}

	Name name;
	Kind kind;
	Type type;
	std::vector<unsigned char> byte_vect;
};

auto operator<<(std::ostream& os, const Symbol::Kind& kind) -> std::ostream& {
	os << kind.kind_str;
	return os;	
}

auto operator<<(std::ostream& os, const Symbol::Type& type) -> std::ostream& {
	os << type.type_str;
	return os;	
}
}

