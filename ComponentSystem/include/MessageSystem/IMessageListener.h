#pragma once
/*
 * IMessageListener.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <InlineSpecification.h>
#include <MessageSystem/MessageSystemId.h>
#include <MessageSystem/IMessageSystemParticipant.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		class IMessageListener : public IMessageSystemParticipant
		{
			public:
				IMessageListener (const MessageSystemId &message_system_id);
				virtual ~IMessageListener ();

				virtual bool operator== ( const IMessageListener &rhs ) const
				{
					return getInternalId() == rhs.getInternalId();
				}

				virtual std::string getName () const = 0;
				virtual void processMessage ( const PackedMessage &msg ) = 0;
                virtual const MessageSystemId getSystemPartId() const {return MessageSystemId("Unknown");}

			private:
				friend class MessageDispatcher;

				UNKNOWNENGINE_INLINE
				int getInternalId () const
				{
					return internal_id;
				}

				UNKNOWNENGINE_INLINE
				void setInternalId ( int id )
				{
					internal_id = id;
				}

				int internal_id;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
