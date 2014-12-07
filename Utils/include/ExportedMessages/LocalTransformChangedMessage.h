#pragma once

#include <MessageSystem/Message.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Core
	{
		template<typename SubObjectIdentifierType>
		UNKNOWNENGINE_ALIGNED_STRUCT(16) LocalTransformChangedMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.LocalTransformChangedMessage";}
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			Transform new_transform;
			SubObjectIdentifierType sub_object_identifier;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
