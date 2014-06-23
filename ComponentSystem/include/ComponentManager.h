#pragma once
/*
 * ComponentManager.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <list>

#include <Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory;
		class ComponentType;
		class Component;

		template<typename K>
		class Properties;

		class ComponentManager : public Singleton<ComponentManager>
		{
			public:
				ComponentManager ();
				virtual ~ComponentManager ();

				virtual void addComponentFactory ( IComponentFactory* factory );
				virtual void removeComponentFactory ( IComponentFactory* factory );

				virtual Component* createComponent ( const ComponentType &component_type, const Properties<std::string> &properties );
				//virtual void destroyComponent (Component* component);

			private:
				std::list<IComponentFactory*>::iterator findFactoryInList ( IComponentFactory* factory );
				IComponentFactory* findFactoryForComponentType ( const ComponentType &component_type );

				int last_used_component_factory_id;

				std::list<IComponentFactory*> component_factories;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
