#ifndef UNKNOWNENGINE_CORE_IMESSAGESYSTEMPARTICIPANT_H
#define UNKNOWNENGINE_CORE_IMESSAGESYSTEMPARTICIPANT_H

#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemId.h>

namespace UnknownEngine {
	namespace Core {

		class IMessageSystemParticipant
		{
			public:

				explicit IMessageSystemParticipant(const MessageSystemId &message_system_id)
					:message_system_id(message_system_id)
				{
				}

				UNKNOWNENGINE_INLINE
				const MessageSystemId& getMessageSystemId() const
				{
					return message_system_id;
				}

			protected:
				MessageSystemId message_system_id;
		};

	} // namespace Core
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_CORE_IMESSAGESYSTEMPARTICIPANT_H
