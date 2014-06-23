/*
 * Win32Window.cpp
 *
 *  Created on: 17 июня 2014 г.
 *      Author: Eaglegor
 */

#include <Window/Win32Window.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		static LRESULT CALLBACK WndProc ( HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam )
		{
			switch ( umessage )
			{
				case WM_DESTROY:
				{
					PostQuitMessage( 0 );
					exit(0);
				}

				case WM_CLOSE:
				{
					PostQuitMessage( 0 );
					exit(0);
				}

				default:
				{
					return DefWindowProc( hwnd, umessage, wparam, lparam );
				}
			}
		}

		Win32Window::Win32Window (const RenderWindowDesc& desc, const HINSTANCE hInstance, const String &name)
		{
			createWindow(desc, hInstance, name);
		}

		Win32Window::~Win32Window ()
		{
			// TODO Auto-generated destructor stub
		}


		WNDCLASSEX Win32Window::createWindowClass ( const RenderWindowDesc& desc, const HINSTANCE hInstance, const String &name ) const
		{
			WNDCLASSEX window_class;

			window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			window_class.lpfnWndProc = WndProc;
			window_class.cbClsExtra = 0;
			window_class.cbWndExtra = 0;
			window_class.hInstance = hInstance;
			window_class.hIcon = LoadIcon( NULL, IDI_WINLOGO );
			window_class.hIconSm = window_class.hIcon;
			window_class.hCursor = LoadCursor( NULL, IDC_ARROW );
			window_class.hbrBackground = static_cast<HBRUSH>( GetStockObject( BLACK_BRUSH ) );
			window_class.lpszMenuName = NULL;
			window_class.lpszClassName = name.c_str();
			window_class.cbSize = sizeof(WNDCLASSEX);

			return window_class;
		}

		void Win32Window::setFullScreen ( bool value )
		{
			if ( value ) ChangeDisplaySettings( &screen_mode, CDS_FULLSCREEN );
			else ChangeDisplaySettings( NULL, 0 );
		}

		void Win32Window::initScreenMode ()
		{
			size_t screen_width = GetSystemMetrics( SM_CXSCREEN );
			size_t screen_height = GetSystemMetrics( SM_CYSCREEN );

			memset( &screen_mode, 0, sizeof( screen_mode ) );
			screen_mode.dmSize = sizeof( screen_mode );
			screen_mode.dmPelsWidth = screen_width;
			screen_mode.dmPelsHeight = screen_height;
			screen_mode.dmBitsPerPel = 32;
			screen_mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		}

		Win32Window::WindowPosition Win32Window::getWindowCenteredPosition ( const size_t window_width, const size_t window_height )
		{
			size_t screen_width = GetSystemMetrics( SM_CXSCREEN );
			size_t screen_height = GetSystemMetrics( SM_CYSCREEN );

			WindowPosition wpos;
			wpos.x = ( screen_width - window_width ) / 2;
			wpos.y = ( screen_height - window_height ) / 2;

			return wpos;
		}

		void Win32Window::createWindow ( const RenderWindowDesc& desc, const HINSTANCE hInstance, const String &name )
		{
			WNDCLASSEX window_class = createWindowClass( desc, hInstance, name );
			RegisterClassEx( &window_class );

			initScreenMode();

			this->setFullScreen( desc.fullscreen );

			WindowPosition wpos;
			if ( desc.fullscreen )
			{
				wpos.x = 0;
				wpos.y = 0;
			}
			else
			{
				wpos = getWindowCenteredPosition( desc.width, desc.height );
			}

			this->window_handle = CreateWindowEx( WS_EX_APPWINDOW, name.c_str(), name.c_str(),
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER | WS_CAPTION | WS_SYSMENU, wpos.x, wpos.y, desc.width, desc.height, NULL, NULL, hInstance, NULL );

			SetWindowLong( window_handle, GWLP_USERDATA, reinterpret_cast<LONG>(this) );
		}

		void Win32Window::show ()
		{
			ShowWindow(window_handle, SW_SHOW);
			SetForegroundWindow(window_handle);
			SetFocus(window_handle);
			//ShowCursor(false);
		}

		void Win32Window::update ()
		{
			MSG msg;
			if( PeekMessage(&msg, 0, 0, 0, PM_REMOVE) )
			{
				WndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
			}
		}


	} /* namespace Graphics */
} /* namespace UnknownEngine */


