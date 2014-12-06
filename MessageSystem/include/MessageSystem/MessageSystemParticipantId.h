#pragma once

#include <MessageSystem_export.h>
#include <string>
#include <NumericIdentifierType.h>
#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemParticipantDictionary.h>

namespace UnknownEngine
{
	namespace Core
	{

		struct MessageSystemParticipantId
		{
			
			enum class AutoRegistrationPolicy
			{
				AUTO_REGISTER,
				DONT_AUTO_REGISTER
			};
			
			MessageSystemParticipantId(const std::string &object_name, AutoRegistrationPolicy auto_registration_policy = AutoRegistrationPolicy::AUTO_REGISTER) :
				name(object_name),
				id(MessageSystemParticipantDictionary::getSingleton()->getMessageParticipantNameId(object_name))
			{
				if (id == INVALID_NUMERIC_IDENTIFIER && auto_registration_policy == AutoRegistrationPolicy::AUTO_REGISTER)
				{
					id = MessageSystemParticipantDictionary::getSingleton()->registerNewMessageParticipant(object_name);
				}
			}

			MessageSystemParticipantId() :
				name(""),
				id(INVALID_NUMERIC_IDENTIFIER)
			{
			}

			MessageSystemParticipantId(const std::string &object_name, const NumericIdentifierType &id) :
				name(object_name),
				id(id)
			{

			}

			UNKNOWNENGINE_INLINE
			bool operator== ( const MessageSystemParticipantId& rhs ) const
			{
				return id == rhs.id;
			}

			std::string name;
			NumericIdentifierType id;
		};
	}
	
}

namespace std
{
	template<>
	struct hash<UnknownEngine::Core::MessageSystemParticipantId>
	{
		typedef UnknownEngine::Core::MessageSystemParticipantId argument_type;
		typedef std::size_t result_type;
		
		result_type operator()(argument_type const& s) const
		{
			return std::hash<UnknownEngine::Core::NumericIdentifierType>()(s.id);
		}
	};
}