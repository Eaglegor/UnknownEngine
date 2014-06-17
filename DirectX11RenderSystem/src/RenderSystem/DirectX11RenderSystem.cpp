/*
 * DirectX10RenderSystem.cpp
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <iostream>

#include <RenderSystem/DirectX11RenderSystem.h>
#include <RenderTargets/DirectX11RenderWindow.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		DirectX11RenderSystem::DirectX11RenderSystem( HINSTANCE hInstance )
				: hInstance( hInstance )
		{
		}

		DirectX11RenderSystem::~DirectX11RenderSystem()
		{
			// TODO Auto-generated destructor stub
		}

		RenderWindow* DirectX11RenderSystem::createRenderWindow( const RenderWindowDesc& windowDesc )
		{
			return new DirectX11RenderWindow(windowDesc, this);
		}

		static const String DX10_RENDER_SYSTEM_NAME("RenderSystem.D3D11");
		String DirectX11RenderSystem::getName () const
		{
			return DX10_RENDER_SYSTEM_NAME;
		}

		void DirectX11RenderSystem::renderFrame ()
		{
			std::cout << "Rendering frame" << std::endl;
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
