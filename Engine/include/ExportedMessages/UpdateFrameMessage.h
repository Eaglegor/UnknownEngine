#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct UpdateFrameMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.MainLoop.UpdateFrameMessage";}

			float dt;
		};

		
	} /* namespace Core */
} /* namespace UnknownEngine */
