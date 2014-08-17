#include <stdafx.h>

#include <Listeners/OgreRenderableComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <Components/Renderables/OgreRenderableComponent.h>

#define MessageProcessor(processor) &OgreRenderableComponentListener::processor

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponentListener::OgreRenderableComponentListener ( const std::string &name, OgreRenderableComponent *component, Core::EngineContext *engine_context )
			: BaseOgreComponentListener< UnknownEngine::Graphics::OgreRenderableComponentListener > ( name ),
			  renderable_component ( component )
		{
			registerProcessor<Core::TransformChangedMessage> ( MessageProcessor ( processTransformChangedMessage ), engine_context );
			registerProcessor<Graphics::ChangeMaterialActionMessage> ( MessageProcessor ( processChangeMaterialActionMessage ), engine_context );
		}

		void OgreRenderableComponentListener::processTransformChangedMessage ( const Core::PackedMessage &msg )
		{
			if ( renderable_component != nullptr )
			{
				renderable_component->onTransformChanged ( transform_changed_unpacker.unpackMessage ( msg ) );
			}
		}

		void OgreRenderableComponentListener::processChangeMaterialActionMessage ( const Core::PackedMessage &msg )
		{
			if ( renderable_component != nullptr )
			{
				renderable_component->doChangeMaterial ( change_material_unpacker.unpackMessage ( msg ) );
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
