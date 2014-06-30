#pragma once

/*
 * Win32Window.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <windows.h>

#include <InlineSpecification.h>
#include <RenderTargets/RenderWindowDesc.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class Win32Window
		{
			public:
				Win32Window ( const RenderWindowDesc& desc, const HINSTANCE hInstance, const String &name );
				virtual ~Win32Window ();

				UNKNOWNENGINE_INLINE
				HWND getWindowHandle ()
				{
					return window_handle;
				}

				void setFullScreen ( bool value );
				void show ();
				void update();

			private:

				struct WindowPosition
				{
						int x, y;
				};

				void initScreenMode ();
				WindowPosition getWindowCenteredPosition ( const size_t window_width, const size_t window_height );
				WNDCLASSEX createWindowClass ( const RenderWindowDesc &desc, const HINSTANCE hInstance, const String &name ) const;
				void createWindow ( const RenderWindowDesc &desc, const HINSTANCE hInstance, const String &name );

				int position_x;
				int position_y;

				DEVMODE screen_mode;
				HWND window_handle;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
