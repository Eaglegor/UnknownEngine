/*
 * ComponentsManager.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <ComponentsManager.h>
#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <Objects/IComponent.h>
#include <algorithm>
#include <Objects/Entity.h>

#define ENABLE_CORE_SUBSYSTEM_INFO_LOG
#define ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#include <CoreLogging.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ComponentsManager* Singleton<ComponentsManager>::instance = nullptr;

		ComponentsManager::ComponentsManager() :
			internal_dictionary ( "ComponentsManager.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER )
		{
		}

		ComponentsManager::~ComponentsManager()
		{
		}

		void ComponentsManager::addComponentFactory ( IComponentFactory* factory )
		{
			if ( factory->getInternalId() != INVALID_NUMERIC_IDENTIFIER ) return;

			NumericIdentifierType new_id = internal_dictionary.registerNewValue ( factory->getName() );
			factory->setInternalId ( new_id );
			component_factories.insert ( std::make_pair ( new_id, factory ) );
		}

		void ComponentsManager::removeComponentFactory ( IComponentFactory* factory )
		{
			if ( factory->getInternalId() == INVALID_NUMERIC_IDENTIFIER ) return;
			component_factories.erase ( factory->getInternalId() );
			internal_dictionary.deleteEntryByKey ( factory->getInternalId() );
			factory->setInternalId ( INVALID_NUMERIC_IDENTIFIER );
		}

		Entity *ComponentsManager::createEntity ( const std::string &name )
		{
			CORE_SUBSYSTEM_INFO ( "Creating entity: " + name );
			Entity* entity = new Entity ( name, this );
			entities.push_back ( entity );
			return entity;
		}

		IComponent* ComponentsManager::createComponent ( const UnknownEngine::Core::ComponentDesc& desc, UnknownEngine::Core::Entity* parent_entity ) throw ( NoSuitableFactoryFoundException )
		{
			CORE_SUBSYSTEM_INFO ( "Creating component '" + desc.name + "' of type '" + desc.type + "' to be attached to the entity '" + parent_entity->getName() + "'" );
			for ( auto & factory : component_factories )
			{
				if ( factory.second->supportsType ( desc.type ) )
				{
					CORE_SUBSYSTEM_INFO ( "Found suitable factory : " + factory.second->getName() );
					IComponent* component = factory.second->createObject ( desc );
					CORE_SUBSYSTEM_INFO ( "Attaching component '" + desc.name + "' to the entity '" + parent_entity->getName() + "'" );
					parent_entity->addComponent ( desc.name, component );
					CORE_SUBSYSTEM_INFO ( "Component '" + desc.name + "' created" );
					return component;
				}
			}
			CORE_SUBSYSTEM_ERROR ( "Not found factory for component type: '" + desc.type + "'" );
			throw NoSuitableFactoryFoundException ( "Can't find factory for component" );
		}

		void ComponentsManager::removeComponent ( IComponent *component )
		{
			CORE_SUBSYSTEM_INFO ( "Destroying component '" + component->getName() + "'" );
			for ( auto & factory : component_factories )
			{
				if ( factory.second->supportsType ( component->getType() ) )
				{
					CORE_SUBSYSTEM_INFO ( "Shutting down component '" + component->getName() + "'" );
					component->shutdown();
					factory.second->destroyObject ( component );
					return;
				}
			}
			CORE_SUBSYSTEM_ERROR ( "No suitable factory found to destroy component '" + component->getName() + "'" );
			throw NoSuitableFactoryFoundException ( "Can't find factory able to destroy component" );
		}

		void ComponentsManager::removeEntity ( Entity* entity )
		{
			if ( entity )
			{
				CORE_SUBSYSTEM_INFO ( "Destroying entity '" + entity->getName() + "'" );
				auto iter = std::find ( entities.begin(), entities.end(), entity );
				if ( iter != entities.end() ) *iter = nullptr;
				delete entity;
			}
		}

		void ComponentsManager::clearEntities()
		{
			for ( Entity * entity : entities )
			{
				removeEntity ( entity );
			}
		}


	} /* namespace Core */
} /* namespace UnknownEngine */

