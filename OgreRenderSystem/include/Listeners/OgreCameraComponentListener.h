#pragma once

#include <unordered_set>
#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <Listeners/BaseOgreComponentListener.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class PackedMessage;
	}

	namespace Graphics
	{

		class OgreCameraComponent;

		class OgreCameraComponentListener : public BaseOgreComponentListener<OgreCameraComponentListener>
		{
			public:
				OgreCameraComponentListener ( const std::string& object_name, OgreCameraComponent* camera_component, Core::EngineContext* engine_context );

			private:
				void processTransformChangedMessage ( const Core::PackedMessage& msg );
				Core::TransformChangedMessageUnpacker transform_message_unpacker;

				OgreCameraComponent* camera_component;
				Core::EngineContext* engine_context;
		};
	}
}