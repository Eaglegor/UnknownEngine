#pragma once
/*
 * Entity.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <map>

#include <Objects/Component.h>

namespace UnknownEngine
{
	namespace Core
	{

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
