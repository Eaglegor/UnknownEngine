/*
 * ComponentManager.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentManager.h>
#include <IComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		template<>
		ComponentManager* Singleton<ComponentManager>::instance = nullptr;

		ComponentManager::ComponentManager() :
				last_used_component_factory_id(0)
		{
			// TODO Auto-generated constructor stub

		}

		ComponentManager::~ComponentManager()
		{
			// TODO Auto-generated destructor stub
		}

		void ComponentManager::addComponentFactory(IComponentFactory* factory)
		{
			if (findFactoryInList(factory) != component_factories.end())
				return;

			if (factory->getInternalId() < 0)
			{
				factory->setInternalId(last_used_component_factory_id);
				++last_used_component_factory_id;
			}

			component_factories.push_back(factory);
		}

		void ComponentManager::removeComponentFactory(
				IComponentFactory* factory)
		{
			auto iter = findFactoryInList(factory);
			if (iter == component_factories.end())
				return;
			component_factories.erase(iter);
		}

		Component* ComponentManager::createComponent(
				const ComponentType& component_type,
				const Properties<std::string>& properties)
		{
			IComponentFactory* factory = findFactoryForComponentType(
					component_type);
			if (factory != nullptr)
				return factory->createComponent(component_type, properties);
			return nullptr;
		}

		std::list<IComponentFactory*>::iterator ComponentManager::findFactoryInList(
				IComponentFactory* factory)
		{
			std::list<IComponentFactory*>::iterator iter =
					component_factories.begin();
			while (iter != component_factories.end())
			{
				if (*factory == (*(*iter)))
					return iter;
				++iter;
			}
			return iter;
		}

		IComponentFactory* ComponentManager::findFactoryForComponentType(
				const ComponentType& component_type)
		{
			for (IComponentFactory* factory : component_factories)
			{
				if (factory->canCreateComponentType(component_type))
					return factory;
			}
			return nullptr;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */

