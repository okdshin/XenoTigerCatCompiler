#ifdef SYMBOLTABLE_UNIT_TEST
#include "SymbolTable.h"
#include <iostream>

using namespace tiger_cat;

auto LookUpTest(const SymbolTable& symbol_table, const Symbol::Name& name) -> void {
	const auto symbol = symbol_table.LookUp(name);
	if(symbol){
		std::cout << *symbol << std::endl;	
	}
	else{
		std::cout << name << " is not in table." << std::endl;	
	}
		
}

int main(int argc, char* argv[])
{
	auto symbol_table = SymbolTable(20);

	symbol_table.Register(Symbol::Create(
		Symbol::Name("num"), Symbol::Kind::Var(), Symbol::Type::Int()));
	
	LookUpTest(symbol_table, Symbol::Name("num"));
	
	LookUpTest(symbol_table, Symbol::Name("count"));
	
	symbol_table.CreateAndSwitchToChildTable();
	
	symbol_table.Register(Symbol::Create(
		Symbol::Name("count"), Symbol::Kind::Var(), Symbol::Type::Int()));
	
	LookUpTest(symbol_table, Symbol::Name("num"));
	
	LookUpTest(symbol_table, Symbol::Name("count"));
	
	symbol_table.Register(Symbol::Create(
		Symbol::Name("num"), Symbol::Kind::Var(), Symbol::Type::Void()));
	
	LookUpTest(symbol_table, Symbol::Name("num"));
	
	symbol_table.DestroyCurrentTableAndSwitchToParentTable();
	
	LookUpTest(symbol_table, Symbol::Name("num"));
	
    return 0;
}

#endif
