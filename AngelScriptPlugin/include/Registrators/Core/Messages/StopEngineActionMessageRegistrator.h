#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>
#include <Registrators/Core/MessageSystem/MessageListenerRegistrator.h>
#include <Registrators/IMessageTypeRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StopEngineActionMessageRegistrator : public PODTypeRegistrator<Core::StopEngineActionMessage >, public IMessageTypeRegistrator
		{
			public:
				StopEngineActionMessageRegistrator() :
					PODTypeRegistrator< Core::StopEngineActionMessage > ( "StopEngineActionMessage", CORE_AS_NAMESPACE_NAME )
				{}
				
				bool registerSender(asIScriptEngine* script_engine) const override
				{
					return MessageSenderRegistrator<Core::StopEngineActionMessage>("Core::StopEngineActionMessage").registerType(script_engine);
				}
				
				bool registerListener(asIScriptEngine* script_engine) const override
				{
					return MessageListenerRegistrator<Core::StopEngineActionMessage>("Core::StopEngineActionMessage").registerType(script_engine);
				}
		};
	}
}
