#include <stdafx.h>
#include <Components/SimpleCreateJointComponent.h>
#include <EngineContext.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>
#include <MessageSystem/MessageSender.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <NameGenerators/NameGenerator.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleCreateJointComponent::SimpleCreateJointComponent ( const std::string& name, const SimpleCreateJointComponentDesc& desc, Core::EngineContext* engine_context ) : 
		Core::BaseComponent ( name.c_str() ),
		desc(desc),
		engine_context(engine_context),
		joint_entity(nullptr),
		change_material_message_sender(name)
		{
			
		}

		SimpleCreateJointComponent::~SimpleCreateJointComponent()
		{

		}

		Core::ComponentType SimpleCreateJointComponent::getType() const
		{
			return SIMPLE_CREATE_JOINT_COMPONENT_TYPE;
		}

		void SimpleCreateJointComponent::init (  )
		{	
				Core::MessageSender<IO::AddSimpleActionMessage> simple_action_message_sender(getName());
				
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
				Core::ComponentsManager* components_manager = engine_context->getComponentsManager();
				Utils::NameGenerator* name_generator = components_manager->getNameGenerator();
				
				joint_entity = components_manager->createEntity( name_generator->generateName() );
				Core::ComponentDesc cdesc;
				cdesc.name = name_generator->generateName();
				cdesc.type = "Physics.Joint.Fixed";
				Core::Properties props;
				props.set<std::string>("actor1_name", desc.body1_name);
				props.set<std::string>("actor2_name", desc.body2_name);
				cdesc.descriptor = props;
				joint_entity->createComponent(cdesc);
				
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

	}
}