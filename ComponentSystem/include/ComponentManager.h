#pragma once
/*
 * ComponentManager.h
 *
 *  Created on: 18 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <IComponentFactory.h>
#include <string>



namespace UnknownEngine
{
	namespace Core
	{

		class ComponentManager
		{
			public:
				ComponentManager ();
				virtual ~ComponentManager ();

				void addComponentFactory(IComponentFactory* factory);

		};

	} /* namespace Core */
} /* namespace UnknownEngine */
