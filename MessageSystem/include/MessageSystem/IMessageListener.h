#pragma once

#include <MessageSystem_export.h>
#include <string>
#include <InlineSpecification.h>
#include <MessageSystem/IMessageSystemParticipant.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		class IMessageListener : public IMessageSystemParticipant
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION ( MessageTypeNotSupportedByListener );

				IMessageListener(const std::string &object_name):
					IMessageSystemParticipant(object_name)
				{

				}

				virtual ~IMessageListener(){}

				UNKNOWNENGINE_INLINE
				bool operator== ( const IMessageListener &rhs ) const
				{
					return getMessageSystemParticipantId() == rhs.getMessageSystemParticipantId();
				}

				MESSAGESYSTEM_EXPORT
				virtual void processMessage ( const PackedMessage &msg ) = 0;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
