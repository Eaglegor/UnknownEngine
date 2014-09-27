#pragma once

#include <MessageSystem/Message.h>
#include <Transform/Transform.h>
#include <AlignedNew.h>

namespace UnknownEngine
{
	namespace Core
	{
		
		/**
		 * @brief Indicates that some subobject changed its local transform in CS of parent object
		 *
		 * \tparam - type of subobject identifier (string, index, guid, etc.)
		 * */
		template<typename SubObjectIdentifierType>
		UNKNOWNENGINE_ALIGNED_STRUCT(16) LocalTransformChangedMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.LocalTransformChangedMessage";}
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;

			Transform new_transform;
			SubObjectIdentifierType sub_object_identifier; ///< Identifier of subobject (number of part, local name etc.)
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
