#pragma once

#include <MessageSystem_export.h>
#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageSystemParticipant
		{
			public:

				explicit IMessageSystemParticipant(const std::string &object_name) :
				message_system_participant_id(object_name, MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER)
				{}

				virtual ~IMessageSystemParticipant(){}

				UNKNOWNENGINE_INLINE
				const MessageSystemParticipantId& getMessageSystemParticipantId() const
				{
					return message_system_participant_id;
				}

				UNKNOWNENGINE_INLINE
				std::string getName () const
				{
					return message_system_participant_id.name;
				}

			protected:
				MessageSystemParticipantId message_system_participant_id;
		};

	} // namespace Core
} // namespace UnknownEngine
