#include <stdafx.h>
#include <Components/SimpleCreateJointComponent.h>
#include <EngineContext.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/ComponentsManager.h>
#include <ComponentSystem/ComponentDesc.h>
#include <NameGenerators/NameGenerator.h>

namespace UnknownEngine
{
	namespace Behavior
	{

		SimpleCreateJointComponent::SimpleCreateJointComponent ( const std::string& name, const SimpleCreateJointComponentDesc& desc) : 
		Core::BaseComponent ( name.c_str() ),
		desc(desc),
		joint_entity(nullptr),
		input_context_mapper(desc.input_context_mapper),
		renderable_component(desc.renderable_component)
		{
			
		}

		SimpleCreateJointComponent::~SimpleCreateJointComponent()
		{

		}

		bool SimpleCreateJointComponent::init (  )
		{	
			if(input_context_mapper)
			{
				input_context_mapper->addSimpleAction(desc.input_context_name.c_str(), desc.create_joint_action_name.c_str(), std::bind(&SimpleCreateJointComponent::switchJoint, this));
			}
			return true;
		}

		void SimpleCreateJointComponent::shutdown()
		{
			if(input_context_mapper)
			{
				input_context_mapper->removeSimpleAction(desc.input_context_name.c_str(), desc.create_joint_action_name.c_str());
			}
			if(joint_entity)
			{
				destroyJoint();
			}
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
				Core::ComponentsManager* components_manager = Core::ComponentsManager::getSingleton();
				Utils::NameGenerator* name_generator = components_manager->getNameGenerator();
				
				joint_entity = components_manager->createEntity( name_generator->generateName() );
				Core::ComponentDesc cdesc;
				cdesc.name = name_generator->generateName();
				cdesc.type = "PhysX.FixedJoint";
				Core::Properties props;
				props.set<std::string>("actor1_name", desc.body1_name);
				props.set<std::string>("actor2_name", desc.body2_name);
				cdesc.descriptor = props;
				joint_entity->createComponent(cdesc);
				
				if(renderable_component)
				{
					renderable_component->setMaterialName(desc.jointed_material_name.c_str());
				}
			}
		}

		void SimpleCreateJointComponent::destroyJoint()
		{
			if(joint_entity)
			{
				Core::ComponentsManager* components_manager = Core::ComponentsManager::getSingleton();
				components_manager->removeEntity(joint_entity);
				joint_entity = nullptr;
				
				if(renderable_component)
				{
					renderable_component->setMaterialName(desc.free_material_name.c_str());
				}
			}
		}

	}
}