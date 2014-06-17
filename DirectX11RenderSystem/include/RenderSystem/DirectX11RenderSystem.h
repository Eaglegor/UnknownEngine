#pragma once

/*
 * DirectX10RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderSystem/RenderSystem.h>
#include <RenderTargets/RenderWindow.h>

#include <Plugins/PluginExport.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX11RenderWindow;

		class DirectX11RenderSystem: public RenderSystem
		{
			public:
				DirectX11RenderSystem (HINSTANCE hInstance);
				virtual ~DirectX11RenderSystem ();

				UNKNOWNENGINE_PLUGIN_INTERFACE
				RenderWindow* createRenderWindow(const RenderWindowDesc &windowDesc) override;

				UNKNOWNENGINE_PLUGIN_INTERFACE
				String getName () const;

				UNKNOWNENGINE_PLUGIN_INTERFACE
				void renderFrame();

				UNKNOWNENGINE_INLINE
				HINSTANCE getHInstance() const {return hInstance;}

			private:
				HINSTANCE hInstance;
				DirectX11RenderWindow* render_window;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
