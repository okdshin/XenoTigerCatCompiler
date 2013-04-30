#ifdef STRING_UNIT_TEST
#include "String.h"
#include <iostream>

using namespace tiger_cat;

int main(int argc, char* argv[])
{
	String str("hello");
	//str.At(0) = Char('e');
	std::cout << str << std::endl;

    return 0;
}

#endif
