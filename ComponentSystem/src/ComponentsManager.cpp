/*
 * ComponentsManager.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <ComponentsManager.h>
#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Core
	{

		class NoSuitableComponentFactoryFound : public Exception{};

		template<>
		ComponentsManager* Singleton<ComponentsManager>::instance = nullptr;

		ComponentsManager::ComponentsManager() :
				last_used_component_factory_id(0)
		{
			// TODO Auto-generated constructor stub

		}

		ComponentsManager::~ComponentsManager()
		{
			// TODO Auto-generated destructor stub
		}

		void ComponentsManager::addComponentFactory(IComponentFactory* factory)
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

		void ComponentsManager::removeComponentFactory(
				IComponentFactory* factory)
		{
			auto iter = findFactoryInList(factory);
			if (iter == component_factories.end())
				return;
			component_factories.erase(iter);
		}

		Entity *ComponentsManager::createEntity(const std::string &name)
		{
			throw Exception("NOT IMPLEMENTED");
		}

		Component* ComponentsManager::createComponent(const ComponentDesc &desc)
		{
			IComponentFactory* factory = findFactoryForComponentType(
					desc.type);
			if (factory != nullptr)
				return factory->createComponent(desc);
			throw NoSuitableComponentFactoryFound();
		}

		std::list<IComponentFactory*>::iterator ComponentsManager::findFactoryInList(
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

		IComponentFactory* ComponentsManager::findFactoryForComponentType(
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

