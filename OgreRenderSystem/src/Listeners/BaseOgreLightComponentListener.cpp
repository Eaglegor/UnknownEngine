#include <stdafx.h>

#include <Listeners/BaseOgreLightComponentListener.h>
#include <Components/Lights/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		BaseOgreLightComponentListener::BaseOgreLightComponentListener ( const std::string& object_name, BaseOgreLightComponent* component, Core::EngineContext* engine_context, OgreRenderSubsystem *render_system):
		BaseOgreComponentListener(object_name, render_system, engine_context),
		component(component)
		{
			registerProcessor<Core::TransformChangedMessage> ( std::bind(&BaseOgreLightComponentListener::processTransformChangedMessage, this, std::placeholders::_1) );
		}

		void BaseOgreLightComponentListener::processTransformChangedMessage ( const Core::PackedMessage& msg )
		{
			component->onTransformChanged( transform_changed_unpacker.unpackMessage(msg) );
		}
		
	}
}