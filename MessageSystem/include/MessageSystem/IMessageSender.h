#pragma once
#include <MessageSystem/IMessageSystemParticipant.h>
#include <MessageSystem_export.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageReceivePolicy;
		class IMessageListener;
		
		class IMessageSender : public IMessageSystemParticipant
		{
		public:
			MESSAGESYSTEM_EXPORT
			IMessageSender(const std::string &name):
			IMessageSystemParticipant(name)
			{}
			
			MESSAGESYSTEM_EXPORT
			virtual ~IMessageSender(){}
			
			MESSAGESYSTEM_EXPORT
			virtual void attachListener(IMessageListener* listener, IMessageReceivePolicy* receive_policy) = 0;

			MESSAGESYSTEM_EXPORT
			virtual void detachListener(IMessageListener* listener) = 0;

			MESSAGESYSTEM_EXPORT
			virtual void detachAllListeners() = 0;
		};
	}
}