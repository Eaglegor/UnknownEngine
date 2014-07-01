#pragma once
/*
 * ComponentFactory.h
 *
 *  Created on: 18 июня 2014 г.
 *      Author: gorbachenko
 */

#include <AbstractObjectFactory.h>
#include <ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{

		class Component;
		class ComponentDesc;

		class IComponentFactory : public AbstractObjectFactory<Component, ComponentType, ComponentDesc>
		{
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
