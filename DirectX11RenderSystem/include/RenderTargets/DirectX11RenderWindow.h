#pragma once

/*
 * DirectX10RenderWindow.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderTargets/RenderWindow.h>

class DirectX11RenderSystem;

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX11RenderWindow: public RenderWindow
		{
			public:
				DirectX11RenderWindow ( const RenderWindowDesc &desc, const DirectX11RenderSystem *render_system );
				virtual ~DirectX11RenderWindow ();

				LRESULT CALLBACK MessageHandler ( HWND window_handler, UINT umsg, WPARAM wparam, LPARAM lparam );

			private:

				struct WindowPosition
				{
					int x, y;
				};

				void initScreenMode();
				WindowPosition getWindowCenteredPosition ( const size_t window_width, const size_t window_height);
				void setFullScreen(bool value);
				WNDCLASSEX createWindowClass ( const RenderWindowDesc &desc ) const;
				void createWindow ( const RenderWindowDesc &desc );
				void showWindow();

				int position_x;
				int position_y;

				DEVMODE screen_mode;
				const DirectX11RenderSystem* render_system;
				HWND window_handle;
		};


	} /* namespace Graphics */
} /* namespace UnknownEngine */
