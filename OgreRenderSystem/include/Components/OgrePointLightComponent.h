#pragma once

#include <Objects/Component.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <Vectors/Vector3.h>
#include <boost/concept_check.hpp>
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
	}

	namespace Graphics
	{

		class OgrePointLightComponentListener;

		class OgreRenderSubsystem;

		static const Core::ComponentType OGRE_POINT_LIGHT_COMPONENT_TYPE = "Graphics.Light.Point";
		
		class OgrePointLightComponent : public Core::Component
		{
			public:
				
				UNKNOWNENGINE_ALIGNED_STRUCT(16) Descriptor
				{
					boost::optional<Math::Scalar> intensity;
					boost::optional<Math::Scalar> attenuation;
					
					Math::Vector3 diffuse_color;
					Math::Vector3 specular_color;
					Core::Transform initial_transform;
					
					Core::LogMessage::Severity log_level;
					
					UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
					
					Descriptor():
					intensity(1.0f),
					attenuation(1.0f),
					diffuse_color(Math::Vector3(1, 1, 1)),
					specular_color(Math::Vector3(1, 1, 1)),
					log_level(Core::LogMessage::LOG_SEVERITY_NONE)
					{}
				};
				
				virtual UnknownEngine::Core::ComponentType getType();
				virtual void shutdown();
				virtual void start();
				virtual void init ( const UnknownEngine::Core::Entity* parent_entity );
				OgrePointLightComponent ( const std::string& name, const Descriptor &desc, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );
				void addReceivedMessageType ( const Core::ReceivedMessageDesc &received_message );
				
				void onTransformChanged(const Core::TransformChangedMessage& msg);

				virtual ~OgrePointLightComponent();
				
				UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
				
			private:
				Core::EngineContext* engine_context;
				OgreRenderSubsystem* render_subsystem;
				Ogre::SceneNode* ogre_scene_node;
				Ogre::Light* ogre_light;
				OgrePointLightComponentListener* listener;
				Core::MessagingPoliciesManager messaging_policies_manager;
				Descriptor desc;
		};
	}
}

#include <AlignedAnyHolder.h>
ALIGNED_BOOST_ANY_HOLDER(UnknownEngine::Graphics::OgrePointLightComponent::Descriptor);