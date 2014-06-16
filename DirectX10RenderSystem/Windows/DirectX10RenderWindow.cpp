/*
 * DirectX10RenderWindow.cpp
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <DirectX10RenderSystem.h>

#include "DirectX10RenderWindow.h"

namespace UnknownEngine
{

	namespace Graphics
	{

		static const LPCSTR WINDOW_NAME = "UnknownEngine";

		static LRESULT CALLBACK WndProc ( HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam )
		{
			DirectX10RenderWindow* render_window = reinterpret_cast<DirectX10RenderWindow*>( GetWindowLong( hwnd, GWLP_USERDATA ) );

			switch ( umessage )
			{
				case WM_DESTROY:
				{
					PostQuitMessage( 0 );
					return 0;
				}

				case WM_CLOSE:
				{
					PostQuitMessage( 0 );
					return 0;
				}

				default:
				{
					return render_window->MessageHandler( hwnd, umessage, wparam, lparam );
				}
			}
		}

		DirectX10RenderWindow::DirectX10RenderWindow ( const RenderWindowDesc &desc, const DirectX10RenderSystem* render_system )
				: render_system( render_system ), window_handle( 0 )
		{
			createWindow( desc );
			showWindow();
		}

		DirectX10RenderWindow::~DirectX10RenderWindow ()
		{
			// TODO Auto-generated destructor stub
		}

		WNDCLASSEX DirectX10RenderWindow::createWindowClass ( const RenderWindowDesc& desc ) const
		{
			WNDCLASSEX window_class;

			window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			window_class.lpfnWndProc = WndProc;
			window_class.cbClsExtra = 0;
			window_class.cbWndExtra = 0;
			window_class.hInstance = render_system->getHInstance();
			window_class.hIcon = LoadIcon( NULL, IDI_WINLOGO );
			window_class.hIconSm = window_class.hIcon;
			window_class.hCursor = LoadCursor( NULL, IDC_ARROW );
			window_class.hbrBackground = static_cast<HBRUSH>( GetStockObject( BLACK_BRUSH ) );
			window_class.lpszMenuName = NULL;
			window_class.lpszClassName = WINDOW_NAME;
			window_class.cbSize = sizeof(WNDCLASSEX);

			return window_class;
		}

		LRESULT DirectX10RenderWindow::MessageHandler ( HWND window_handler, UINT umsg, WPARAM wparam, LPARAM lparam )
		{
			return DefWindowProc( window_handler, umsg, wparam, lparam );
		}

		void DirectX10RenderWindow::setFullScreen ( bool value )
		{
			if ( value ) ChangeDisplaySettings( &screen_mode, CDS_FULLSCREEN );
			else ChangeDisplaySettings( NULL, 0 );
		}

		void DirectX10RenderWindow::initScreenMode ()
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

		DirectX10RenderWindow::WindowPosition DirectX10RenderWindow::getWindowCenteredPosition ( const size_t window_width, const size_t window_height )
		{
			size_t screen_width = GetSystemMetrics( SM_CXSCREEN );
			size_t screen_height = GetSystemMetrics( SM_CYSCREEN );

			WindowPosition wpos;
			wpos.x = ( screen_width - window_width ) / 2;
			wpos.y = ( screen_height - window_height ) / 2;

			return wpos;
		}

		void DirectX10RenderWindow::createWindow ( const RenderWindowDesc& desc )
		{
			WNDCLASSEX window_class = createWindowClass( desc );
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

			this->window_handle = CreateWindowEx( WS_EX_APPWINDOW, WINDOW_NAME, WINDOW_NAME,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, wpos.x, wpos.y, desc.width, desc.height, NULL, NULL, render_system->getHInstance(), NULL );

			SetWindowLong( window_handle, GWLP_USERDATA, reinterpret_cast<LONG>(this) );
		}

		void DirectX10RenderWindow::showWindow ()
		{
			ShowWindow(window_handle, SW_SHOW);
			SetForegroundWindow(window_handle);
			SetFocus(window_handle);
			ShowCursor(false);
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
