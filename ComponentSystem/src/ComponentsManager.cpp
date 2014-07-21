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

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ComponentsManager* Singleton<ComponentsManager>::instance = nullptr;

		ComponentsManager::ComponentsManager() :
			internal_dictionary(NUMERIC_IDENTIFIER_INITIAL_VALUE, INVALID_NUMERIC_IDENTIFIER)
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
			throw Exception("NOT IMPLEMENTED");
		}

		Component* ComponentsManager::createComponent(const ComponentDesc &desc, const Entity *parent_entity) throw (NoSuitableFactoryFoundException)
		{
			for( auto &factory : component_factories )
			{
				if(factory.second->supportsType(desc.type))
				{
					Component* component = factory.second->createObject(desc);
					component->init(parent_entity);
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

	} /* namespace Core */
} /* namespace UnknownEngine */

