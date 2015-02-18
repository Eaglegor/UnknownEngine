#pragma once
#include <InlineSpecification.h>
#include <Components/SimpleBehaviorComponent.h>
#include <Quaternion.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <Descriptors/SimpleRotationComponentDesc.h>

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
			
			static const Core::ComponentType& getCType();

			explicit SimpleRotationComponent ( const std::string& name, const SimpleRotationComponentDesc& desc, Core::EngineContext* engine_context );
			virtual ~SimpleRotationComponent();
				
			UNKNOWNENGINE_INLINE
			virtual Core::ComponentType getType() const override {return SIMPLE_ROTATION_COMPONENT_TYPE;}
			
			virtual void init ( const Core::IEntity* parent_entity ) override;
			virtual void shutdown() override;
			
			virtual void act(Math::Scalar dt) override;
			
			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			static const Core::ComponentType component_type;

			SimpleRotationComponentDesc desc;
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;
			
			Core::EngineContext* engine_context;
			Math::Scalar current_angle;
			Math::Quaternion quaterion;
		};
	}
}