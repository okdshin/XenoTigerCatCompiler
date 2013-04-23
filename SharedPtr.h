#pragma once
//SharedPtr:20130424
#include <iostream>
#include <memory>

namespace ticket
{
	template<class T>
	using SharedPtr = std::shared_ptr<T>;
}

