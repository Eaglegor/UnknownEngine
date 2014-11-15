#pragma once

#include <iostream>

namespace UnknownEngine
{
	namespace Utils
	{
		class SimpleFpsPrinter
		{
		public:
			void operator()(size_t fps)
			{
				std::cout << "Average fps: " << fps << std::endl;
			}
		};
	}
}