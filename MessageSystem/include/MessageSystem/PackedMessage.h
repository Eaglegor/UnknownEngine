#pragma once
#include <MessageSystem_export.h>
#include <string>
#include <boost/any.hpp>

#include <InlineSpecification.h>
#include <MessageSystem/MessageType.h>
#include <MessageSystem/MessageDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{
		class PackedMessage
		{
			public:
				template<typename T>
				PackedMessage ( const T& message):
				message_type_id ( MESSAGE_TYPE_ID(T::getTypeName()) ), 
				message_container(message)
				{
				}

				// This comstructor is used to speedup message type lookup with caching
				template<typename T>
				PackedMessage ( const T& message, MessageType message_type ):
				message_type_id ( message_type ), 
				message_container(message)
				{
				}
				
				
				virtual ~PackedMessage ()
				{
				}

				UNKNOWNENGINE_INLINE
				virtual MessageType getMessageTypeId () const
				{
					return message_type_id;
				}

				template<typename T>
				UNKNOWNENGINE_INLINE
				const T& get() const
				{
					return boost::any_cast<const T&>(message_container);
				}
				
			private:
				MessageType message_type_id;
				boost::any message_container;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
