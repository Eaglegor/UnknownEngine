#pragma once

/*
 * RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <PluginInterfaceSpecification.h>

#include "RenderWindow.h"

namespace UnknownEngine
{
	namespace Graphics
	{
		class RenderSystem
		{
			public:

				UNKNOWNENGINE_PLUGIN_INTERFACE
				virtual RenderWindow* createRenderWindow( const RenderWindowDesc &desc ) = 0;

				UNKNOWNENGINE_PLUGIN_INTERFACE
				virtual String getName() const = 0;

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
