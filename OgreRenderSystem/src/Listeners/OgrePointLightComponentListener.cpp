#include <Listeners/OgrePointLightComponentListener.h>
#include <Components/OgrePointLightComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgrePointLightComponentListener::OgrePointLightComponentListener ( const std::string& object_name, UnknownEngine::Graphics::OgrePointLightComponent* component ):
		BaseOgreComponentListener< OgrePointLightComponentListener >(object_name),
		component(component)
		{
		}

		void OgrePointLightComponentListener::processTransformChangedMessage ( const Core::PackedMessage& msg )
		{
			component->onTransformChanged( transform_changed_unpacker.unpackMessage(msg) );
		}
		
	}
}