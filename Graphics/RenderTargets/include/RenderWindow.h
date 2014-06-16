#pragma once

/*
 * RenderWindow.h
 *
 *  Created on: 15 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include "RenderWindowDesc.h"

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
				RenderWindow ( const RenderWindowDesc &desc )
				{
				}

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
