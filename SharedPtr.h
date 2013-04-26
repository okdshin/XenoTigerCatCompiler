#pragma once
//SharedPtr:20130424
#include <iostream>
#include <memory>

namespace tiger_cat
{
	template<class T>
	using SharedPtr = std::shared_ptr<T>;
}

