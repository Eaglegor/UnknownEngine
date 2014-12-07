#pragma once

#include <MessageSystem_export.h>
#include <unordered_map>
#include <Singleton.h>
#include <NumericIdentifierType.h>
#include <MessageSystem/MessageType.h>
#include <Dictionary.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core
	{

		class MessageDictionary : public Singleton<MessageDictionary>
		{
			public:

				typedef Utils::Dictionary<MessageType, std::string> InternalDictionaryType;

				MessageDictionary ();
				virtual ~MessageDictionary ();

				MESSAGESYSTEM_EXPORT
				MessageType registerNewMessageType ( const std::string &message_type_name );

				MESSAGESYSTEM_EXPORT
				bool messageTypeIsRegistered ( const MessageType &type_id ) const;

				MESSAGESYSTEM_EXPORT
				bool messageTypeIsRegistered ( const std::string &type_id ) const;

				MESSAGESYSTEM_EXPORT
				std::string getMessageTypeName ( const MessageType &type_id ) const ;

				MESSAGESYSTEM_EXPORT
				MessageType getMessageTypeId ( const std::string &type_name ) const ;

			private:
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
		Core::MessageType val = Core::MessageDictionary::getSingleton()->getMessageTypeId(message_type_name);
		if(val == Core::INVALID_NUMERIC_IDENTIFIER)
		{
			val = Core::MessageDictionary::getSingleton()->registerNewMessageType(message_type_name);
		}
		return val;
	}
	
	UNKNOWNENGINE_INLINE
	std::string MESSAGE_TYPE_NAME(const Core::MessageType& message_type_id)
	{
		return Core::MessageDictionary::getSingleton()->getMessageTypeName(message_type_id);
	}
	
} /* namespace UnknownEngine */
