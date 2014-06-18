#pragma once
/*
 * ComponentFactory.h
 *
 *  Created on: 18 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */
#include <Objects/Component.h>
#include <Properties.h>

namespace UnknownEngine
{
	namespace Core
	{

		class IComponentFactory
		{
			public:
				virtual ~IComponentFactory ();

				virtual Component* createInstance(const Properties &properties) = 0;

			private:
				IComponentFactory ();
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
