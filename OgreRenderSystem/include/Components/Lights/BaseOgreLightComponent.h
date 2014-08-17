#pragma once

#include <Objects/Component.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>
#include <OgreColourValue.h>

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
		class LogHelper;
	}

	namespace Graphics
	{

		class BaseOgreLightComponentListener;

		class OgreRenderSubsystem;

		struct OgreLightSettings
		{
			struct Attenuation
			{
				Math::Scalar range;
				Math::Scalar constant;
				Math::Scalar linear;
				Math::Scalar quadratic;
			};
			
			boost::optional<Attenuation> attenuation;
			boost::optional<bool> cast_shadows;
			
			Math::Scalar intensity;
			Ogre::ColourValue diffuse_color;
			Ogre::ColourValue specular_color;
			
			OgreLightSettings():
			diffuse_color(1,1,1),
			specular_color(1,1,1),
			intensity(1)
			{}
			
		};
		
		class BaseOgreLightComponent : public Core::Component
		{
			public:
				virtual UnknownEngine::Core::ComponentType getType() = 0;
				virtual void shutdown();
				virtual void start();
				virtual void init ( const UnknownEngine::Core::Entity* parent_entity );
				BaseOgreLightComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, const OgreLightSettings& light_settings );
				void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );
				
				void onTransformChanged(const Core::TransformChangedMessage& msg);

				virtual ~BaseOgreLightComponent();
				
			protected:
				OgreLightSettings light_settings;
				Ogre::Light* ogre_light;
				Ogre::SceneNode* ogre_scene_node;
				Core::LogHelper* log_helper;

			private:
				Core::EngineContext* engine_context;
				OgreRenderSubsystem* render_subsystem;
				BaseOgreLightComponentListener* listener;
				Core::MessagingPoliciesManager messaging_policies_manager;
		};
	}
}
