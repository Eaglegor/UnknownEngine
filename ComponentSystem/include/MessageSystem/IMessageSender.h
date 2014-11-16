#pragma once
#include "IMessageSystemParticipant.h"

namespace UnknownEngine
{
	namespace Core
	{

		class IMessageReceivePolicy;
		class IMessageListener;
		
		class IMessageSender : public IMessageSystemParticipant
		{
		public:
			IMessageSender(const std::string &name):
			IMessageSystemParticipant(name)
			{}
			
			virtual ~IMessageSender(){}
			
			virtual void attachListener(IMessageListener* listener, IMessageReceivePolicy* receive_policy) = 0;
			virtual void detachListener(IMessageListener* listener) = 0;
		};
	}
}