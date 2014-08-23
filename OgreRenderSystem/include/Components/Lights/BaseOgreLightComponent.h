#pragma once

#include <OgreRenderSubsystem_fwd.h>
#include <Components/BaseOgreComponent.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Descriptors/Components/Lights/OgreLightSettings.h>

namespace Ogre
{
	class Light;
	class SceneNode;
}

namespace UnknownEngine
{
	namespace Core
	{

		struct TransformChangedMessage;
		class EngineContext;
	}

	namespace Graphics
	{

		class BaseOgreLightComponentListener;
	
		class BaseOgreLightComponent : public BaseOgreComponent
		{
			public:
				BaseOgreLightComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, const OgreLightSettings& light_settings );
				virtual ~BaseOgreLightComponent();
				
				virtual UnknownEngine::Core::ComponentType getType() = 0;
				
				void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );
				
				void onTransformChanged(const Core::TransformChangedMessage& msg);

			protected:
				virtual void internalInit(const Core::Entity* parent_entity) override;
				virtual void internalShutdown() override;
				
				OgreLightSettings light_settings;
				
				Ogre::Light* ogre_light;
				Ogre::SceneNode* ogre_scene_node;
				
			private:
				BaseOgreLightComponentListener* listener;
		};
	}
}
