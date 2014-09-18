#pragma once

#include <MessageSystem/Message.h>
#include <Transform/Transform.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Indicates that some simulation object changed its world transform
		 */
		struct TransformChangedMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.TransformChangedMessage";}
			
			Transform new_transform;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
