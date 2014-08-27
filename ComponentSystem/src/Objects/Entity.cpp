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

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
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

		void Entity::addComponent ( const std::string &name, IComponent *component )
		{
			if ( components.find ( name ) != components.end() ) throw DuplicateComponentNameException ( "Duplicate component name: " + name );

			CORE_SUBSYSTEM_INFO ( "Initializing component '" + component->getName() + "'" );
			component->init ( this );
			components[name] = component;
		}

		void Entity::removeComponent ( const std::string &name )
		{
			if ( components.find ( name ) != components.end() ) throw ComponentNotFoundException ( "Can't find the component with the name " + name );
			components_manager->removeComponent ( components[name] );
			components.erase ( name );
		}

		const std::string &Entity::getName()
		{
			return name;
		}

		void Entity::start()
		{
			for ( auto & iter : components )
			{
				iter.second->start();
			}
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
