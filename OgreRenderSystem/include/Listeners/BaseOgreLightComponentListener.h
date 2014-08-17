#pragma once

#include <Listeners/BaseOgreComponentListener.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class BaseOgreLightComponent;
		
		class BaseOgreLightComponentListener : public UnknownEngine::Graphics::BaseOgreComponentListener<BaseOgreLightComponentListener>
		{
			public:
				BaseOgreLightComponentListener ( const std::string& object_name, BaseOgreLightComponent* component );
				
			private:
				void processTransformChangedMessage ( const Core::PackedMessage &msg );
				Core::TransformChangedMessageUnpacker transform_changed_unpacker;
				
				BaseOgreLightComponent* component;
		};
	}
}

