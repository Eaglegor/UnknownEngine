#pragma once

#include <ComponentSystem_export.h>
#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemParticipantId.h>

namespace UnknownEngine
{
	namespace Core
	{

		/**
		 * @brief Base class for all who wants to send/receive messages through message system
		 *
		 * ###Concept
		 * To send/receive messages classes need to have the unique address. One can get and save such address
		 * manually but it's easier not to do this and just inherit the message sending/receiving class from
		 * some common base class which takes care of registering/unregistering the class name and storing
		 * it's address. IMessageSystemParticipant is such class.
		 *
		 * ###Usage
		 * You just inherit from IMessageSystemParticipant and pass the object name to it's constructor.
		 * After constructor's call you can get your address calling getMessageSystemParticipantId(). That's all.
		 * When you call a destructor, it automatically unregisters your object.
		 *
		 */
		class IMessageSystemParticipant
		{
			public:

				/**
				 * @brief Constructor
				 * @param message_system_participant_id - **unique** object name
				 */
				COMPONENTSYSTEM_EXPORT
				explicit IMessageSystemParticipant ( const std::string &object_name );

				COMPONENTSYSTEM_EXPORT
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
				std::string getName () const
				{
					return message_system_participant_id.name;
				}

			protected:
				MessageSystemParticipantId message_system_participant_id; ///< Identifier in message system
		};

	} // namespace Core
} // namespace UnknownEngine
