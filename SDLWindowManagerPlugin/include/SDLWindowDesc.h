#pragma once

#include <string>

namespace UnknownEngine
{
	namespace GUI
	{
		
		struct SDLWindowDesc
		{
			std::string window_name;
			std::string window_title;
			size_t width;
			size_t height;
			
			bool resizable;
			bool full_screen;
		};
		
	}
}