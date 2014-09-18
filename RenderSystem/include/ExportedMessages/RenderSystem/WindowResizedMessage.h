#pragma once

#include <string>
#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct WindowResizedMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.GUI.WindowResizedMessage";}
			
			std::string window_name;
			size_t width;
			size_t height;
		};
	}
}