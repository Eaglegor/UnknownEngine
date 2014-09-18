#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Engine stop command
		 *
		 * Stops engine
		 */
		struct StopEngineActionMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.StopEngineActionMessage";}
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
