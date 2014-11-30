#pragma once

#include <Registrators/ClassValueTypeRegistrator.h>
#include <Registrators/PODTypeRegistrator.h>
#include <Registrators/Core/ASNamespaceName.h>
#include <ExportedMessages/StopEngineActionMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <Registrators/Core/MessageSystem/MessageSenderRegistrator.h>
#include <Registrators/Core/MessageSystem/MessageListenerRegistrator.h>

namespace UnknownEngine
{
	namespace Behavior
	{
		class UpdateFrameMessageRegistrator: public ClassValueTypeRegistrator<Core::UpdateFrameMessage >
		{
			public:
				UpdateFrameMessageRegistrator() :
					ClassValueTypeRegistrator< Core::UpdateFrameMessage > ( "UpdateFrameMessage", CORE_AS_NAMESPACE_NAME )
				{}
				
				virtual bool registerRelatedTypes ( asIScriptEngine* script_engine ) const override
				{
					return MessageSenderRegistrator<Core::UpdateFrameMessage>("Core::UpdateFrameMessage").registerType(script_engine) &&
					MessageListenerRegistrator<Core::UpdateFrameMessage>("Core::UpdateFrameMessage").registerType(script_engine);
				}
		};
	}
}
