#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class StopEngineActionMessageRegistrator : public PODTypeRegistrator<Core::StopEngineActionMessage >
		{
			public:
				PropertiesRegistrator() :
					PODTypeRegistrator< Core::StopEngineActionMessage > ( "StopEngineActionMessage", CORE_AS_NAMESPACE_NAME )
				{}
				
				void registerMessageSender(asIScriptEngine* script_engine)
				{
					MessageSenderRegistrator<Core::StopEngineActionMessage>("Core::StopEngineActionMessage").registerType(script_engine);
				}
		};
	}
}
