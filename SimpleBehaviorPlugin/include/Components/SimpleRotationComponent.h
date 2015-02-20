#pragma once
#include <InlineSpecification.h>
#include <Components/SimpleBehaviorComponent.h>
#include <Quaternion.h>
#include <Vectors/Vector3.h>
#include <AlignedNew.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <Descriptors/SimpleRotationComponentDesc.h>
#include <Components/Transform/ITransformHolderComponent.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
	}

	namespace Behavior
	{
		
		static const Core::ComponentType SIMPLE_ROTATION_COMPONENT_TYPE = Core::ComponentType("Behavior.SimpleRotation", Core::ComponentType(Core::ITransformHolderComponent::getTypeName()));
		
		UNKNOWNENGINE_ALIGNED_CLASS(16) SimpleRotationComponent : public SimpleBehaviorComponent, Core::ITransformHolderComponent
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
			
			virtual Math::Vector3 getPosition();
			virtual Math::Quaternion getOrientation();
			virtual Math::Transform getTransform();

			UNKNOWNENGINE_ALIGNED_NEW_OPERATOR;
			
		private:
			static const Core::ComponentType component_type;

			SimpleRotationComponentDesc desc;
			Core::MessageSender<Core::TransformChangedMessage> transform_changed_message_sender;
			
			Math::Transform current_transform;
			Core::EngineContext* engine_context;
			Math::Scalar current_angle;
			Math::Quaternion quaterion;
		};
	}
}