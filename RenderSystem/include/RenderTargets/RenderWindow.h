#pragma once

/*
 * RenderWindow.h
 *
 *  Created on: 15 июня 2014 г.
 *      Author: Eaglegor
 */

#include <RenderTargets/RenderWindowDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class RenderWindow
		{
			public:
				virtual ~RenderWindow ()
				{
				}

			protected:
				RenderWindow ()
				{
				}

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
