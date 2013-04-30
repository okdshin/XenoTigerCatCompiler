#ifdef SYMBOL_UNIT_TEST
#include "Symbol.h"
#include <iostream>

using namespace tiger_cat;

int main(int argc, char* argv[])
{
	std::cout << Symbol::Kind::Var() << std::endl;;
	const auto symbol = Symbol::Create(
		Symbol::Name("name"), Symbol::Kind::Var(), Symbol::Type::Int());
	std::cout << *symbol << std::endl;


    return 0;
}

#endif
