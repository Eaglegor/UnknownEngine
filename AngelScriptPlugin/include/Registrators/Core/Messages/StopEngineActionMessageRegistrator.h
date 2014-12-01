#pragma once

#include <Registrators/MessageTypeRegistrator.h>
#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>
#include <Registrators/Core/MessageSystem/MessageListenerRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StopEngineActionMessageRegistrator : public MessageTypeRegistrator<Core::StopEngineActionMessage >
		{
			public:
				StopEngineActionMessageRegistrator() :
					MessageTypeRegistrator< Core::StopEngineActionMessage > ( "StopEngineActionMessage", CORE_AS_NAMESPACE_NAME )
				{}
				
				virtual bool registerRelatedTypes ( asIScriptEngine* script_engine ) const override
				{
					return MessageSenderRegistrator<Core::StopEngineActionMessage>("Core::StopEngineActionMessage").registerType(script_engine) &&
					MessageListenerRegistrator<Core::StopEngineActionMessage>("Core::StopEngineActionMessage").registerType(script_engine);
				}
		};
	}
}
