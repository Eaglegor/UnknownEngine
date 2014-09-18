#pragma once

#include <MessageSystem/Message.h>

#include <WindowHandle.h>
#include <string>
#include <functional>

namespace UnknownEngine
{
	namespace Graphics
	{

		struct GetWindowHandleMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.GUI.GetWindowHandleMessage";}
			
			std::string requested_window_name;
			std::function<void(const NativeWindowHandleType&)> result_callback;
		};
		
	}
}