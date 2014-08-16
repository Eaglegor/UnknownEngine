#pragma once

#include <Listeners/BaseOgreComponentListener.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgrePointLightComponent;
		
		class OgrePointLightComponentListener : public UnknownEngine::Graphics::BaseOgreComponentListener<OgrePointLightComponentListener>
		{
			public:
				OgrePointLightComponentListener ( const std::string& object_name, OgrePointLightComponent* component );
				
			private:
				void processTransformChangedMessage ( const Core::PackedMessage &msg );
				Core::TransformChangedMessageUnpacker transform_changed_unpacker;
				
				OgrePointLightComponent* component;
		};
	}
}

