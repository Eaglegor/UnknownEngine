#pragma once

#include <MessageSystem/IMessageListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_map>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>

namespace UnknownEngine {

	namespace Core
	{
		class EngineContext;
	}

	namespace Graphics {

		class OgreRenderableComponent;

		class OgreRenderableComponentListener : public Core::IMessageListener
		{
			public:
				OgreRenderableComponentListener(const std::string &name, OgreRenderableComponent* component, Core::EngineContext* engine_context);

				void processMessage(const Core::PackedMessage &msg);

			private:
				typedef void (OgreRenderableComponentListener::*MessageProcessor)(const Core::PackedMessage&);
				std::unordered_map<Core::MessageType, MessageProcessor> message_processors;

				template<typename T>
				void registerProcessor(MessageProcessor processor, Core::EngineContext* engine_context);

				void processTransformChangedMessage(const Core::PackedMessage &msg);
				Core::TransformChangedMessageUnpacker transform_changed_unpacker;

				void processChangeMaterialActionMessage(const Core::PackedMessage &msg);
				Graphics::ChangeMaterialActionMessageUnpacker change_material_unpacker;

				OgreRenderableComponent* renderable_component;
		};

	} // namespace Graphics
} // namespace UnknownEngine
