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

#include <Singleton.h>
#include <ComponentType.h>
#include <Exception.h>
#include <NumericIdentifierType.h>
#include <Dictionary.h>
#include <NoSuitableFactoryFoundException.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory;
		class Component;
		class ComponentDesc;
		class SubsystemDesc;
		class Entity;

		class ComponentsManager : public Singleton<ComponentsManager>
		{
			public:
				ComponentsManager ();
				virtual ~ComponentsManager ();

				virtual void addComponentFactory ( IComponentFactory* factory );
				virtual void removeComponentFactory ( IComponentFactory* factory );

				virtual Entity* createEntity ( const std::string &name );
				virtual Component* createComponent ( const ComponentDesc &desc ) throw (NoSuitableFactoryFoundException);

			private:
				std::unordered_map<NumericIdentifierType, IComponentFactory*> component_factories;
				Utils::Dictionary<NumericIdentifierType, std::string> internal_dictionary;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
