#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Frame synchronization message
		 *
		 * This message is broadcasted every frame by MainLoop.
		 * It may be sent more than once per frame.
		 *
		 */
		struct UpdateFrameMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.MainLoop.UpdateFrameMessage";}

			float dt; ///< Delta time from last frame
		};

		
	} /* namespace Core */
} /* namespace UnknownEngine */
