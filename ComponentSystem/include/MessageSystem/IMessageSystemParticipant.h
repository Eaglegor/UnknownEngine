#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine {
	namespace Core {

		class IMessageSystemParticipant
		{
			public:

				explicit IMessageSystemParticipant(const MessageSystemParticipantId &message_system_participant_id);
				virtual ~IMessageSystemParticipant();

				UNKNOWNENGINE_INLINE
				const MessageSystemParticipantId& getMessageSystemParticipantId() const
				{
					return message_system_participant_id;
				}

				UNKNOWNENGINE_INLINE
				std::string getName () const {return message_system_participant_id.name;}

			protected:
				MessageSystemParticipantId message_system_participant_id;
		};

	} // namespace Core
} // namespace UnknownEngine
