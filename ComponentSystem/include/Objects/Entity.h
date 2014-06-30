#pragma once
/*
 * Entity.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <map>

namespace UnknownEngine
{
	namespace Core
	{

		class Component;

		class Entity
		{
			public:
				Entity (std::string name);
				virtual ~Entity ();

				void addComponent(std::string name, Component* component);
				void removeComponent(std::string name);

			private:
				std::map<std::string, Component*> components;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
