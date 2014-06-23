#pragma once

/*
 * RenderSystem.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Plugins/PluginInterfaceSpecification.h>

#include <RenderTargets/RenderWindow.h>

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
				virtual void renderFrame() = 0;

				UNKNOWNENGINE_PLUGIN_INTERFACE
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
