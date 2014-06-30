#pragma once
/*
 * IMessageListener.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <InlineSpecification.h>
#include <MessageSystem/IMessageSystemParticipant.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		class IMessageListener : public IMessageSystemParticipant
		{
			public:
				IMessageListener (const MessageSystemParticipantId &message_system_participant_id);
				virtual ~IMessageListener ();

				virtual bool operator== ( const IMessageListener &rhs ) const
				{
					return getMessageSystemParticipantId() == rhs.getMessageSystemParticipantId();
				}

				virtual void processMessage ( const PackedMessage &msg ) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
