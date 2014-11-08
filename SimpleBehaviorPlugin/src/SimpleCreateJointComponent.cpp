#include <stdafx.h>
#include <SimpleCreateJointComponent.h>
#include <EngineContext.h>
#include <Objects/Entity.h>
#include <ComponentsManager.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleCreateJointComponent::SimpleCreateJointComponent ( const std::string& name, const SimpleCreateJointComponentDesc& desc, Core::EngineContext* engine_context ) : 
		SimpleBehaviorComponent ( name ),
		desc(desc),
		engine_context(engine_context),
		joint_entity(nullptr),
		change_material_message_sender(name, engine_context)
		{
			
		}

		SimpleCreateJointComponent::~SimpleCreateJointComponent()
		{

		}

		Core::ComponentType SimpleCreateJointComponent::getType()
		{
			return SIMPLE_CREATE_JOINT_COMPONENT_TYPE;
		}

		void SimpleCreateJointComponent::init ( const Core::Entity* parent_entity )
		{	
				Core::MessageSender<IO::AddSimpleActionMessage> simple_action_message_sender(getName(), engine_context);
				
				IO::AddSimpleActionMessage msg;
				msg.context_name = desc.input_context_name;
				msg.action_slot_name = desc.create_joint_action_name;
				msg.action_callback = std::bind(&SimpleCreateJointComponent::switchJoint, this);
				simple_action_message_sender.sendMessage(msg);
		}

		void SimpleCreateJointComponent::shutdown()
		{
			
		}

		void SimpleCreateJointComponent::switchJoint()
		{
			if(!joint_entity)
			{
				createJoint();
			}
			else
			{
				destroyJoint();
			}
		}
		
		void SimpleCreateJointComponent::createJoint()
		{
			if(!joint_entity)
			{
				joint_entity = engine_context->getComponentsManager()->createEntity(std::string(getName()) + ".JointEntity" );
				Core::ComponentDesc cdesc;
				cdesc.name = joint_entity->getName() + ".Joint";
				cdesc.type = "Physics.Joint.Fixed";
				Core::Properties props;
				props.set<std::string>("actor1_name", desc.body1_name);
				props.set<std::string>("actor2_name", desc.body2_name);
				cdesc.descriptor = props;
				engine_context->getComponentsManager()->createComponent(cdesc, joint_entity);
				
				Graphics::ChangeMaterialActionMessage msg;
				msg.new_material_name = desc.jointed_material_name;
				change_material_message_sender.sendMessage(msg);
			}
		}

		void SimpleCreateJointComponent::destroyJoint()
		{
			if(joint_entity)
			{
				engine_context->getComponentsManager()->removeEntity(joint_entity);
				joint_entity = nullptr;
				
				Graphics::ChangeMaterialActionMessage msg;
				msg.new_material_name = desc.free_material_name;
				change_material_message_sender.sendMessage(msg);
			}
		}

		
		void SimpleCreateJointComponent::act ( Math::Scalar dt )
		{
		}

		
	}
}