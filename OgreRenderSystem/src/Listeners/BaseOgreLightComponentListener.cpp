#include <Listeners/BaseOgreLightComponentListener.h>
#include <Components/Lights/BaseOgreLightComponent.h>

#define MessageProcessor(processor) &BaseOgreLightComponentListener::processor

namespace UnknownEngine
{
	namespace Graphics
	{
		BaseOgreLightComponentListener::BaseOgreLightComponentListener ( const std::string& object_name, UnknownEngine::Graphics::BaseOgreLightComponent* component, Core::EngineContext* engine_context, OgreRenderSubsystem *render_system):
		BaseOgreComponentListener< BaseOgreLightComponentListener >(object_name, render_system),
		component(component)
		{
			registerProcessor<Core::TransformChangedMessage> ( MessageProcessor ( processTransformChangedMessage ), engine_context );
		}

		void BaseOgreLightComponentListener::processTransformChangedMessage ( const Core::PackedMessage& msg )
		{
			component->onTransformChanged( transform_changed_unpacker.unpackMessage(msg) );
		}
		
	}
}