#pragma once

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		class SimpleFpsPrinter
		{
		public:
			SimpleFpsPrinter(std::string prefix):
			prefix(prefix)
			{}
			
			void operator()(size_t fps)
			{
				std::cout << prefix << fps << std::endl;
			}
			
		private:
			std::string prefix;
		};
	}
}