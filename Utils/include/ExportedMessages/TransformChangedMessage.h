#pragma once

#include <MessageSystem/Message.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Indicates that some simulation object changed its world transform
		 */
		UNKNOWNENGINE_ALIGNED_STRUCT(16) TransformChangedMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.TransformChangedMessage";}
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			Transform new_transform;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Core::TransformChangedMessage);