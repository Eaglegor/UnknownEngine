/*
 * Entity.cpp
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <Objects/Entity.h>

namespace UnknownEngine
{
	namespace Core
	{

		Entity::Entity (const std::string &name):name(name)
		{
		}

		Entity::~Entity ()
		{
		  // TODO Auto-generated destructor stub
		}

		const std::string &Entity::getName()
		{
		  return name;
		}

	} /* namespace Core */
} /* namespace UnknownEngine */
