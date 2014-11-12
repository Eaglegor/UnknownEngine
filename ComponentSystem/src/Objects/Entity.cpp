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
			for ( auto & iter : components )
			{
				components_manager->removeComponent ( iter.second );
			}
		}

		void Entity::addComponent ( IComponent *component )
		{
			if ( components.find ( component->getName() ) != components.end() ) throw DuplicateComponentNameException ( "Component already added: " + std::string(component->getName()) );

			CORE_SUBSYSTEM_INFO ( "Initializing component '" + component->getName() + "'" );
			component->init ( this );
			components[component->getName()] = component;
		}

		void Entity::removeComponent ( IComponent *component )
		{
			if ( components.find ( std::string(component->getName()) ) != components.end() ) throw ComponentNotFoundException ( "Entity doesn't contain component " + std::string(component->getName()) );
			components_manager->removeComponent ( components[component->getName()] );
			components.erase ( name );
		}

		const std::string &Entity::getName()
		{
			return name;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
