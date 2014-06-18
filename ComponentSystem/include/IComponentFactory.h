#pragma once
/*
 * ComponentFactory.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <unordered_set>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{

		class Properties;
		class Component;
		class ComponentType;

		class IComponentFactory
		{
			public:
				virtual ~IComponentFactory ();

				virtual bool operator== ( const IComponentFactory &rhs ) const
				{
					return getName() == rhs.getName();
				}

				virtual std::string getName () const = 0;
				virtual Component* createComponent ( const ComponentType &component_type, const Properties &properties ) = 0;
				virtual bool canCreateComponentType ( const ComponentType &component_type_name ) const = 0;
				virtual const std::unordered_set<ComponentType>& getSupportedComponentTypeNames () const = 0;

			private:
				IComponentFactory ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
