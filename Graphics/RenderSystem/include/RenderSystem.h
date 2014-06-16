#pragma once

/*
 * RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */
#include "RenderWindow.h"

namespace UnknownEngine
{
	namespace Graphics
	{
		class RenderSystem
		{
			public:
				virtual RenderWindow* createRenderWindow ( const RenderWindowDesc &desc ) = 0;

				virtual ~RenderSystem ()
				{
				}

			protected:
				RenderSystem ()
				{
				}
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
