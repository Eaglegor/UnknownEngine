/*
 * Entity.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <ComponentsManager.h>
#include <Objects/Entity.h>
#include <Objects/IComponent.h>
#include <ComponentDesc.h>

//#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#include <CoreLogging.h>

namespace UnknownEngine
{
	namespace Core
	{

		Entity::Entity ( const std::string &name, ComponentsManager* components_manager ) :
			name ( name ),
			components_manager ( components_manager )
		{
		}

		Entity::~Entity ()
		{
			
		}

		IComponent* Entity::createComponent ( const ComponentDesc& desc )
		{
			if ( components.find ( desc.name ) != components.end() ) throw DuplicateComponentNameException ( "Component already created: " + std::string(desc.name) + " (Entity: " + getName() +")" );
			CORE_SUBSYSTEM_INFO ( "Initializing component '" + desc.name + "'" );
			IComponent* component = components_manager->createComponent(desc);
			component->init ( this );
			components.emplace(desc.name, component);
			return component;
		}

		void Entity::removeAllComponents()
		{
			for(auto &iter : components)
			{
				iter.second->shutdown();
				components_manager->removeComponent(iter.second);
			}
			components.clear();
		}
	
		void Entity::removeComponent ( IComponent *component )
		{
			if ( components.find ( std::string(component->getName()) ) != components.end() ) throw ComponentNotFoundException ( "Entity doesn't contain component " + std::string(component->getName()) );
			components.erase ( name );
			component->shutdown();
			components_manager->removeComponent ( component );
		}

		std::string Entity::getName() const
		{
			return name;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
