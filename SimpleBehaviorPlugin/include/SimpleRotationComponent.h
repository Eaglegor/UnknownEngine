#pragma once
#include <InlineSpecification.h>
#include <SimpleBehaviorComponent.h>
#include <Quaternion.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		
		static const Core::ComponentType SIMPLE_ROTATION_COMPONENT_TYPE = "Behavior.SimpleRotation";
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) SimpleRotationComponent : public SimpleBehaviorComponent
		{
		public:
			explicit SimpleRotationComponent ( const std::string& name, Core::EngineContext* engine_context );
			virtual ~SimpleRotationComponent();
				
			UNKNOWNENGINE_INLINE
			virtual Core::ComponentType getType(){return SIMPLE_ROTATION_COMPONENT_TYPE;}
			
			virtual void init ( const Core::Entity* parent_entity );
			virtual void shutdown();
			
			virtual void act(Math::Scalar dt);
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;
			
			Core::EngineContext* engine_context;
			Math::Scalar current_angle;
			Math::Quaternion quaterion;
		};
	}
}