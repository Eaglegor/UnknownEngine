#pragma once

#include <MessageSystem_export.h>
#include <MessageSystem/Policies/Listener/MessageReceivePolicyType.h>

namespace UnknownEngine
{
	namespace Core
	{
		struct MessageReceivePolicyDesc;
		class IMessageReceivePolicy;
		
		class IMessageReceivePolicyFactory
		{
			public:
				MESSAGESYSTEM_EXPORT
				virtual ~IMessageReceivePolicyFactory(){}

				MESSAGESYSTEM_EXPORT
				virtual const char* getName() const = 0;

				MESSAGESYSTEM_EXPORT
				virtual bool supportsType ( const MessageReceivePolicyType &object_type ) const = 0;

				MESSAGESYSTEM_EXPORT
				virtual IMessageReceivePolicy* createObject ( const MessageReceivePolicyDesc& desc ) = 0;

				MESSAGESYSTEM_EXPORT
				virtual void destroyObject ( IMessageReceivePolicy* object ) = 0;
		};

	} // namespace Core
} // namespace UnknownEngine
