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
	}

	namespace Graphics
	{

		class OgreCameraComponent;

		class OgreCameraComponentListener : public BaseOgreComponentListener<OgreCameraComponentListener>
		{
			public:
				virtual void processMessage ( const UnknownEngine::Core::PackedMessage& msg );

				OgreCameraComponentListener ( const std::string& object_name, OgreCameraComponent* camera_component, Core::EngineContext* engine_context );

			private:
				void processTransformChangedMessage ( const PackedMessage& msg );
				Core::TransformChangedMessageUnpacker transform_message_unpacker;

				OgreCameraComponent* camera_component;
				Core::EngineContext* engine_context;
		};
	}
}