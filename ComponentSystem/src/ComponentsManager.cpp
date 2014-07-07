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
			factory->setInternalId(INVALID_NUMERIC_IDENTIFIER);
		}

		Entity *ComponentsManager::createEntity(const std::string &name)
		{
			throw Exception("NOT IMPLEMENTED");
		}

		Component* ComponentsManager::createComponent(const ComponentDesc &desc) throw (NoSuitableFactoryFoundException)
		{
			for( auto &factory : component_factories )
			{
				if(factory.second->supportsType(desc.type)) return factory.second->createObject(desc);
			}
			throw NoSuitableFactoryFoundException("Can't find factory for component");
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

