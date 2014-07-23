#include <stdafx.h>

#include <Listeners\OgreRenderableComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <Components/OgreRenderableComponent.h>

#define MessageProcessor(processor) &OgreRenderableComponentListener::processor

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderableComponentListener::OgreRenderableComponentListener(const std::string &name, OgreRenderableComponent *component, Core::EngineContext *engine_context)
			:Core::IMessageListener(name)
		{

			registerProcessor<Core::TransformChangedMessage>(MessageProcessor(processTransformChangedMessage), engine_context);
			registerProcessor<Graphics::ChangeMaterialActionMessage>(MessageProcessor(processChangeMaterialActionMessage), engine_context);
		}

		void OgreRenderableComponentListener::processMessage(const Core::PackedMessage &msg)
		{
			(this->*message_processors[msg.getMessageTypeId()])(msg);
		}

		void OgreRenderableComponentListener::processTransformChangedMessage(const Core::PackedMessage &msg)
		{
			renderable_component->onTransformChanged( transform_changed_unpacker.unpackMessage(msg) );
		}

		void OgreRenderableComponentListener::processChangeMaterialActionMessage(const Core::PackedMessage &msg)
		{
			renderable_component->doChangeMaterial( change_material_unpacker.unpackMessage(msg) );
		}

		template <typename T>
		void OgreRenderableComponentListener::registerProcessor(OgreRenderableComponentListener::MessageProcessor processor, Core::EngineContext *engine_context)
		{
			Core::MessageType msg_type = engine_context->getMessageDictionary()->getMessageTypeId(T::getTypeName());
			message_processors[msg_type] = processor;
		}

	} // namespace Graphics
} // namespace UnknownEngine
