/*
 * ComponentManager.cpp
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <ComponentManager.h>
#include <IComponentFactory.h>

namespace UnknownEngine
{
	namespace Core
	{

		ComponentManager* ComponentManager::instance = nullptr;

		ComponentManager::ComponentManager ()
		{
			// TODO Auto-generated constructor stub

		}

		ComponentManager::~ComponentManager ()
		{
			// TODO Auto-generated destructor stub
		}

		void ComponentManager::addComponentFactory ( IComponentFactory* factory )
		{
			if ( findFactoryInList( factory ) == component_factories.end() ) return;
			component_factories.push_back( factory );
		}

		void ComponentManager::removeComponentFactory ( IComponentFactory* factory )
		{
			auto iter = findFactoryInList( factory );
			if ( iter == component_factories.end() ) return;
			component_factories.erase( iter );
		}

		Component* ComponentManager::createComponent ( const ComponentType& component_type, const Properties& properties )
		{
			IComponentFactory* factory = findFactoryForComponentType( component_type );
			if ( factory != nullptr ) return factory->createComponent( component_type, properties );
			return nullptr;
		}

		std::list<IComponentFactory*>::iterator ComponentManager::findFactoryInList ( IComponentFactory* factory )
		{
			std::list<IComponentFactory*>::iterator iter = component_factories.begin();
			while ( iter != component_factories.end() )
			{
				if ( *factory == ( *( *iter ) ) ) return iter;
				++iter;
			}
			return iter;
		}

		ComponentManager* ComponentManager::getSingleton ()
		{
			if ( instance == nullptr )
			{
				instance = new ComponentManager();
			}
			return instance;
		}

		IComponentFactory* ComponentManager::findFactoryForComponentType ( const ComponentType& component_type )
		{
			for ( IComponentFactory* factory : component_factories )
			{
				if ( factory->canCreateComponentType( component_type ) ) return factory;
			}
			return nullptr;
		}

		void ComponentManager::initInstance ( ComponentManager* manager )
		{
			if(instance == nullptr) instance = manager;
		}


	} /* namespace Core */
} /* namespace UnknownEngine */

