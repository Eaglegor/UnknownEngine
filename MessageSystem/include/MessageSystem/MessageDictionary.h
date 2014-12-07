#pragma once

#include <MessageSystem_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <MessageSystem/MessageType.h>
#include <Dictionary.h>
#include <InlineSpecification.h>
#include <mutex>

namespace UnknownEngine
{

	namespace Core
	{

		class MessageDictionary : public Singleton<MessageDictionary>
		{
			public:
				MessageDictionary ();
				virtual ~MessageDictionary ();

				MESSAGESYSTEM_EXPORT
				MessageType registerNewMessageType ( const char* message_type_name );

				MESSAGESYSTEM_EXPORT
				bool messageTypeIsRegistered ( const MessageType &type_id ) const;

				MESSAGESYSTEM_EXPORT
				bool messageTypeIsRegistered ( const char* type_id ) const;

				MESSAGESYSTEM_EXPORT
				const char* getMessageTypeName ( const MessageType &type_id ) const ;

				MESSAGESYSTEM_EXPORT
				MessageType getMessageTypeId ( const char* type_name );
				
			private:
				typedef Utils::Dictionary<MessageType, std::string> InternalDictionaryType;
				InternalDictionaryType internal_dictionary;
		};

#ifdef _MSC_VER
#ifndef MessageSystem_EXPORTS
		extern template class MESSAGESYSTEM_EXPORT Singleton<MessageDictionary>;
#else
		template class MESSAGESYSTEM_EXPORT Singleton<MessageDictionary>;
#endif
#endif

	} /* namespace Core */

	UNKNOWNENGINE_INLINE
	Core::MessageType MESSAGE_TYPE_ID(const std::string& message_type_name)
	{
		return Core::MessageDictionary::getSingleton()->getMessageTypeId(message_type_name.c_str());
	}
	
	UNKNOWNENGINE_INLINE
	std::string MESSAGE_TYPE_NAME(const Core::MessageType& message_type_id)
	{
		return std::string(Core::MessageDictionary::getSingleton()->getMessageTypeName(message_type_id));
	}
	
} /* namespace UnknownEngine */
