#pragma once

/*
 * DirectX10RenderWindow.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <RenderWindow.h>

class DirectX10RenderSystem;

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX10RenderWindow: public RenderWindow
		{
			public:
				DirectX10RenderWindow ( const RenderWindowDesc &desc, const DirectX10RenderSystem *render_system );
				virtual ~DirectX10RenderWindow ();

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
				HWND window_handle;
				const DirectX10RenderSystem* render_system;
		};


	} /* namespace Graphics */
} /* namespace UnknownEngine */
