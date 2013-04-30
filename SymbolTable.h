#pragma once
//SymbolTable:20130425
#include <iostream>
#include "SharedPtr.h"
#include "String.h"
#include "Symbol.h"
#include "HashMap.h"

namespace tiger_cat
{
class SymbolTable {
public:
	using HashMapPtr = SharedPtr<HashMap<Symbol::Name, Symbol::Ptr>>;
	
	SymbolTable(unsigned int table_size) : 
			table_size(table_size),
			current_table_index(0), 
			symbol_map_vect(){
		CreateChildTable();
	}
	
	auto CreateAndSwitchToChildTable() -> void {
		CreateChildTable();
		++current_table_index;
	}

	auto DestroyCurrentTableAndSwitchToParentTable() -> void {
		symbol_map_vect.resize(current_table_index);	
		--current_table_index;
	}

	auto Register(const Symbol::Ptr& symbol) -> void {
		CurrentTable()->Insert(symbol->GetName(), symbol);
	}

	auto LookUp(const Symbol::Name& name)const -> Symbol::Ptr {
		int temp_current_table_index = static_cast<int>(current_table_index);
		while(temp_current_table_index >= 0)
		{
			auto element_ptr = symbol_map_vect.at(temp_current_table_index)->Find(name);
			if(element_ptr){
				return element_ptr->GetValue();
			}
			--temp_current_table_index;
		}
		return Symbol::Ptr();	
	}
private:
	auto CurrentTable()const -> HashMapPtr {
		return symbol_map_vect.at(current_table_index);	
	}
	auto CreateChildTable() -> void {
		symbol_map_vect.push_back(HashMapPtr(new HashMap<Symbol::Name, Symbol::Ptr>(
			table_size,
			[](const Symbol::Name& name) -> unsigned int {
				unsigned int sum = 0;
				unsigned int count = 1;
				for(unsigned int index = 0; index < name.Size(); ++index){
					sum += name.At(index).ToUnsignedInt()*count;
					count*=2;
				}
				return sum;
			})));
	}

	unsigned int table_size;
	unsigned int current_table_index;
	std::vector<HashMapPtr> symbol_map_vect;
};

}

