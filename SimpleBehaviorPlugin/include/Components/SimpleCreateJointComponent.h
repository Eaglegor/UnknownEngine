#pragma once
#include <Components/SimpleBehaviorComponent.h>
#include <Descriptors/SimpleCreateJointComponentDesc.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
	}

	namespace Behavior
	{
		static const Core::ComponentType SIMPLE_CREATE_JOINT_COMPONENT_TYPE = "Behavior.SimpleCreateJoint";
		
		class SimpleCreateJointComponent : public Core::BaseComponent
		{
		public:
			SimpleCreateJointComponent ( const std::string& name, const SimpleCreateJointComponentDesc &desc, Core::EngineContext* engine_context );
			virtual ~SimpleCreateJointComponent();
			
			virtual Core::ComponentType getType() const override;
			virtual void init () override;
			virtual void shutdown() override;
			
		private:
			void switchJoint();
			void createJoint();
			void destroyJoint();
			
			SimpleCreateJointComponentDesc desc;
			
			Core::EngineContext* engine_context;
			Core::IEntity* joint_entity;
			
			Core::MessageSender<Graphics::ChangeMaterialActionMessage> change_material_message_sender;
		};
	}
}