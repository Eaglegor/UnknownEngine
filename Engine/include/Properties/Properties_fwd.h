#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename T>
		class PropertiesTree;

		typedef PropertiesTree<std::string> Properties;
	}
}
