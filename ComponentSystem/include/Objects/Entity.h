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
				Entity (const std::string &name);
				virtual ~Entity ();

				void addComponent(const std::string &name, const Component* component);
				void removeComponent(const std::string &name);
				const std::string& getName();

			private:
				std::map<std::string, Component*> components;
				std::string name;

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
