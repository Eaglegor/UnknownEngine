#pragma once

#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine {
	namespace Core {

		/**
		 * @brief Base class for all who wants to send/receive messages through message system
		 *
		 * Just holds the message system participant id
		 *
		 */
		class IMessageSystemParticipant
		{
			public:

				/**
				 * @brief Constructor
				 * @param message_system_participant_id - unique message system participant identifier
				 */
				explicit IMessageSystemParticipant(const MessageSystemParticipantId &message_system_participant_id);
				virtual ~IMessageSystemParticipant();

				/**
				  * @brief Returns message system participant's identifier
				  * @return %Message system participnat's identifier
				  */
				UNKNOWNENGINE_INLINE
				const MessageSystemParticipantId& getMessageSystemParticipantId() const
				{
					return message_system_participant_id;
				}

				/**
				  * @brief Returns name of message system participant
				  * @return %Message system participant's name
				  */
				UNKNOWNENGINE_INLINE
				std::string getName () const {return message_system_participant_id.name;}

			protected:
				MessageSystemParticipantId message_system_participant_id; ///< Identifier in message system
		};

	} // namespace Core
} // namespace UnknownEngine
