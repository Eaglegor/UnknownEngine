#pragma once

#include <Objects/Component.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <Transform/Transform.h>
#include <ExportedMessages/LogMessage.h>

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

		UNKNOWNENGINE_ALIGNED_STRUCT(16) OgreLightSettings
		{
			struct Attenuation
			{
				Math::Scalar range;
				Math::Scalar constant;
				Math::Scalar linear;
				Math::Scalar quadratic;
			};
			
			boost::optional<Attenuation> attenuation;
			
			Math::Scalar intensity;
			Math::Vector3 diffuse_color;
			Math::Vector3 specular_color;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
			OgreLightSettings():
			diffuse_color(Math::Vector3(1,1,1)),
			specular_color(Math::Vector3(1,1,1)),
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
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR
				
			protected:
				OgreLightSettings light_settings;
				Ogre::Light* ogre_light;
				Ogre::SceneNode* ogre_scene_node;
				void setLogHelper(Core::LogHelper* log_helper);

			private:
				Core::EngineContext* engine_context;
				OgreRenderSubsystem* render_subsystem;
				BaseOgreLightComponentListener* listener;
				Core::MessagingPoliciesManager messaging_policies_manager;
				Core::LogHelper* log_helper;
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgreLightSettings);