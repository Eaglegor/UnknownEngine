#include <stdafx.h>

#include <Listeners/OgreRenderableComponentListener.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDictionary.h>
#include <Components/Renderables/OgreRenderableComponent.h>

#define MessageProcessor(processor) std::bind(&OgreRenderableComponentListener::processor, this)

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponentListener::OgreRenderableComponentListener ( const std::string &name, OgreRenderableComponent *component, Core::EngineContext *engine_context, OgreRenderSubsystem *render_system )
			: BaseOgreComponentListener ( name, render_system, engine_context ),
			  renderable_component ( component )
		{
			registerProcessor<Core::TransformChangedMessage> ( std::bind(&OgreRenderableComponentListener::processTransformChangedMessage, this, std::placeholders::_1) );
			registerProcessor<Graphics::ChangeMaterialActionMessage> ( std::bind(&OgreRenderableComponentListener::processChangeMaterialActionMessage, this, std::placeholders::_1) );
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
