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
#include <Objects/Component.h>
#include <algorithm>
#include <Objects/Entity.h>
#include <CoreLogging.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ComponentsManager* Singleton<ComponentsManager>::instance = nullptr;

		ComponentsManager::ComponentsManager() :
			internal_dictionary("ComponentsManager.Dictionary", NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER)
		{
		}

		ComponentsManager::~ComponentsManager()
		{
		}

		void ComponentsManager::addComponentFactory(IComponentFactory* factory)
		{
			if (factory->getInternalId() != INVALID_NUMERIC_IDENTIFIER) return;

			NumericIdentifierType new_id = internal_dictionary.registerNewValue(factory->getName());
			factory->setInternalId(new_id);
			component_factories.insert( std::make_pair(new_id, factory) );
		}

		void ComponentsManager::removeComponentFactory(IComponentFactory* factory)
		{
			if(factory->getInternalId() == INVALID_NUMERIC_IDENTIFIER) return;
			component_factories.erase(factory->getInternalId());
			internal_dictionary.deleteEntryByKey(factory->getInternalId());
			factory->setInternalId(INVALID_NUMERIC_IDENTIFIER);
		}

		Entity *ComponentsManager::createEntity(const std::string &name)
		{
			return new Entity(name, this);
		}

		Component* ComponentsManager::createComponent(const ComponentDesc &desc, const Entity *parent_entity) throw (NoSuitableFactoryFoundException)
		{
			CORE_SUBSYSTEM_INFO("Creating component '" + desc.name + "' of type '" + desc.type + "'");
			for( auto &factory : component_factories )
			{
				if(factory.second->supportsType(desc.type))
				{
					Component* component = factory.second->createObject(desc);
					CORE_SUBSYSTEM_INFO("Initializing component '" + desc.name + "'");
					component->init(parent_entity);
					CORE_SUBSYSTEM_INFO("Component '" + desc.name + "' created");
					return component;
				}
			}
			throw NoSuitableFactoryFoundException("Can't find factory for component");
		}

		void ComponentsManager::removeComponent(Component *component)
		{
			for( auto &factory : component_factories )
			{
				component->shutdown();
				if(factory.second->supportsType(component->getType())) return factory.second->destroyObject(component);
			}
			throw NoSuitableFactoryFoundException("Can't find factory able to destroy component");
		}

		COMPONENTSYSTEM_EXPORT
			void ComponentsManager::removeEntity( Entity* entity )
		{
			if(entity) delete entity;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

