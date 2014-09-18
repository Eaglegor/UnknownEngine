#pragma once

#include <MessageSystem/Message.h>
#include <Transform/Transform.h>

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
		struct LocalTransformChangedMessage : public Message
		{
			constexpr static const char* getTypeName(){return "Engine.LocalTransformChangedMessage";}
			
			Transform new_transform;
			SubObjectIdentifierType sub_object_identifier; ///< Identifier of subobject (number of part, local name etc.)
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
