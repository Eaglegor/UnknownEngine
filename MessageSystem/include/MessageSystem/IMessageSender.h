#pragma once
#include <MessageSystem_export.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageReceivePolicy;
		class IMessageListener;
		
		class IMessageSender
		{
		public:
			MESSAGESYSTEM_EXPORT
			virtual ~IMessageSender(){}
			
			MESSAGESYSTEM_EXPORT
			virtual const char* getName() = 0;
			
			MESSAGESYSTEM_EXPORT
			virtual void attachListener(IMessageListener* listener) = 0;

			MESSAGESYSTEM_EXPORT
			virtual void detachListener(IMessageListener* listener) = 0;

			MESSAGESYSTEM_EXPORT
			virtual void detachAllListeners() = 0;
		};
	}
}
