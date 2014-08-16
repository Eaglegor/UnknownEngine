#include <Listeners/BaseOgreLightComponentListener.h>
#include <Components/BaseOgreLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		BaseOgreLightComponentListener::BaseOgreLightComponentListener ( const std::string& object_name, UnknownEngine::Graphics::BaseOgreLightComponent* component ):
		BaseOgreComponentListener< BaseOgreLightComponentListener >(object_name),
		component(component)
		{
		}

		void BaseOgreLightComponentListener::processTransformChangedMessage ( const Core::PackedMessage& msg )
		{
			component->onTransformChanged( transform_changed_unpacker.unpackMessage(msg) );
		}
		
	}
}