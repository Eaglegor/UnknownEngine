#pragma once
/*
 * ComponentsManager.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <string>
#include <list>
#include <vector>

#include <Objects/Component.h>
#include <Singleton.h>


namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory;
		class Component;
		class ComponentDesc;
		class Entity;

		class ComponentsManager : public Singleton<ComponentsManager>
		{
			public:
				ComponentsManager ();
				virtual ~ComponentsManager ();

				virtual void addComponentFactory ( IComponentFactory* factory );
				virtual void removeComponentFactory ( IComponentFactory* factory );

				virtual Entity* createEntity ( const std::string &name );
				virtual Component* createComponent ( const ComponentDesc &desc );
				//virtual void destroyComponent (Component* component);

			private:
				std::list<IComponentFactory*>::iterator findFactoryInList ( IComponentFactory* factory );
				IComponentFactory* findFactoryForComponentType ( const ComponentType &component_type );

				int last_used_component_factory_id;

				std::list<IComponentFactory*> component_factories;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
