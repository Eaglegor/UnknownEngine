#pragma once
/*
 * ComponentManager.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <string>
#include <list>

namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory;
		class ComponentType;
		class Component;

		template<typename K>
		class Properties;

		class ComponentManager
		{
			public:
				virtual ~ComponentManager ();

				virtual void addComponentFactory ( IComponentFactory* factory );
				virtual void removeComponentFactory ( IComponentFactory* factory );

				virtual Component* createComponent ( const ComponentType &component_type, const Properties<std::string> &properties );

				static ComponentManager* getSingleton();
				static void initInstance(ComponentManager* manager);

			private:
				ComponentManager ();

				std::list<IComponentFactory*>::iterator findFactoryInList ( IComponentFactory* factory );
				IComponentFactory* findFactoryForComponentType ( const ComponentType &component_type );

				std::list<IComponentFactory*> component_factories;

				static ComponentManager* instance;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
