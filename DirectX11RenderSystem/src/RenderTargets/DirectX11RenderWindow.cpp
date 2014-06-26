/*
 * DirectX10RenderWindow.cpp
 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */
#include <stdafx.h>

#include <Window/Win32Window.h>
#include <RenderSystem/DirectX11RenderSystem.h>
#include <RenderTargets/DirectX11RenderWindow.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		DirectX11RenderWindow::DirectX11RenderWindow ( const RenderWindowDesc &desc, const DirectX11RenderSystem* render_system )
				: render_system( render_system ), window( nullptr )
		{
			window = new Win32Window(desc, render_system->getHInstance(), render_system->getName());
			window->show();
		}

		DirectX11RenderWindow::~DirectX11RenderWindow ()
		{
			if(window != nullptr)
			{
				delete window;
			}
		}

		void DirectX11RenderWindow::update ()
		{
			window->update();
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
