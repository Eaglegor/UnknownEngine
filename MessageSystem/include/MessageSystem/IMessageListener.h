#pragma once

#include <MessageSystem_export.h>
#include <string>
#include <InlineSpecification.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class PackedMessage;

		class IMessageListener
		{
			public:
				MESSAGESYSTEM_EXPORT
				virtual ~IMessageListener(){}
				
				MESSAGESYSTEM_EXPORT
				virtual const char* getName() const = 0;

				MESSAGESYSTEM_EXPORT
				virtual void processMessage ( const PackedMessage &msg ) = 0;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
