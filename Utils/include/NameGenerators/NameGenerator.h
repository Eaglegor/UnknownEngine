#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Utils
	{
		class NameGenerator
		{
		public:
			virtual std::string generateName() = 0;
			virtual ~NameGenerator(){}
		};
	}
}