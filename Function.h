#pragma once
//Function:20130430
#include <iostream>
#include <functional>

namespace tiger_cat
{
	template<class R, class... Args>
	using Function = std::function<R (Args...)>;
}

