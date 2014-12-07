#pragma once

#include <Components/BaseOgreComponent.h>
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

		class OgreRenderSubsystem;
		class BaseOgreLightComponentListener;
	
		class BaseOgreLightComponent : public BaseOgreComponent
		{
			public:
				BaseOgreLightComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, const OgreLightSettings& light_settings );
				virtual ~BaseOgreLightComponent();
				
				void onTransformChanged(const Core::TransformChangedMessage& msg);

			protected:
				virtual void internalInit(const Core::IEntity* parent_entity) override;
				virtual void internalShutdown() override;
				
				virtual void initMessageListenerBuffers ( bool can_be_multi_threaded ) override;
				
				OgreLightSettings light_settings;
				
				Ogre::Light* ogre_light;
				Ogre::SceneNode* ogre_scene_node;
		};
	}
}
