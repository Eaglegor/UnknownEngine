#pragma once

#include <Listeners/BaseOgreComponentListener.h>
#include <MessageSystem/MessageType.h>
#include <unordered_map>
#include <unordered_set>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}

	namespace Graphics
	{

		class OgreRenderableComponent;

		class OgreRenderableComponentListener : public BaseOgreComponentListener<OgreRenderableComponentListener>
		{
			public:
				OgreRenderableComponentListener ( const std::string& name, UnknownEngine::Graphics::OgreRenderableComponent* component, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Graphics::OgreRenderSubsystem* render_system );

			private:
				void processTransformChangedMessage ( const Core::PackedMessage &msg );
				Core::TransformChangedMessageUnpacker transform_changed_unpacker;

				void processChangeMaterialActionMessage ( const Core::PackedMessage &msg );
				Graphics::ChangeMaterialActionMessageUnpacker change_material_unpacker;

				OgreRenderableComponent* renderable_component;
		};

	} // namespace Graphics
} // namespace UnknownEngine
