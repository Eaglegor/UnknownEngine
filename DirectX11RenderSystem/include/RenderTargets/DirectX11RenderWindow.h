#pragma once

/*
 * DirectX11RenderWindow.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <RenderTargets/RenderWindow.h>

class DirectX11RenderSystem;

namespace UnknownEngine
{
	namespace Graphics
	{

		class Win32Window;

		class DirectX11RenderWindow: public RenderWindow
		{
			public:
				DirectX11RenderWindow ( const RenderWindowDesc &desc, const DirectX11RenderSystem *render_system );
				virtual ~DirectX11RenderWindow ();

				void update();

			private:
				const DirectX11RenderSystem* render_system;
				Win32Window *window;
		};


	} /* namespace Graphics */
} /* namespace UnknownEngine */
