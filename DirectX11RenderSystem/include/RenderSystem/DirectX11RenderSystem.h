#pragma once

/*
 * DirectX11RenderSystem.h
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>
#include <RenderSystem/RenderSystem.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX11RenderWindow;
		class RenderWindow;

		class DirectX11RenderSystem: public RenderSystem
		{
			public:
				DirectX11RenderSystem (HINSTANCE hInstance);
				virtual ~DirectX11RenderSystem ();

				RenderWindow* createRenderWindow(const RenderWindowDesc &windowDesc) override;

				String getName () const;

				void renderFrame();

				HINSTANCE getHInstance() const {return hInstance;}

			private:
				HINSTANCE hInstance;
				DirectX11RenderWindow* render_window;

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
