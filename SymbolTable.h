#pragma once
//SymbolTable:20130425
#include <iostream>
#include "SharedPtr.h"
#include "String.h"

namespace ticket
{
class Symbol {
public:
	using Ptr = SharedPtr<Symbol>;
	using Name = String;
	
	class Kind {
	public:
		Kind(const std::string& kind_str):kind_str(kind_str){}
		static auto Var() -> Kind {
			return Kind("Var");	
		}
		static auto Func() -> Kind {
			return Kind("Func");	
		}
		auto operator==(const Kind& kind) -> bool {
			return this->kind_str == kind.kind_str;
		}

	private:
		std::string kind_str;
	};

	class Type {
	public:
		Type(const std::string& type_str) : type_str(type_str){}
		static auto Int() -> Type {
			return Type("Int");	
		}
		static auto Void() -> Type {
			return Type("Void");	
		}
	private:
		std::string type_str;
	};

	static auto Create(
			const Name& name, const Kind& kind, const Type& type) -> Ptr {
		return Ptr(new Symbol(name, kind, type));	
	}


private:
	Symbol(const Name& name, const Kind& kind, const Type& type) 
		: name(name), kind(kind), type(type){}

	Name name;
	Kind kind;
	Type type;
	std::vector<unsigned char> byte_vect;
};
/*
class SymbolTable{
public:
    SymbolTable(){}

private:
	std::unordered_map<String, Symbol::Ptr> symbol_vect;

};
*/
}

