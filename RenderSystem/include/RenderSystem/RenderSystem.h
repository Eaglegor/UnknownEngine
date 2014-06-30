#pragma once

/*
 * RenderSystem.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <RenderTargets/RenderWindow.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		class RenderSystem
		{
			public:

				virtual RenderWindow* createRenderWindow( const RenderWindowDesc &desc ) = 0;
				virtual void renderFrame() = 0;
				virtual std::string getName() const = 0;

				virtual ~RenderSystem()
				{
				}

			protected:
				RenderSystem()
				{
				}
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
