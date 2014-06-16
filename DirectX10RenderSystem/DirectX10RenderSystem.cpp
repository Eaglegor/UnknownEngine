/*
 * DirectX10RenderSystem.cpp
 *
 *  Created on: 16 ���� 2014 �.
 *      Author: Eaglegor
 */

#include "DirectX10RenderSystem.h"
#include <DirectX10RenderWindow.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		DirectX10RenderSystem::DirectX10RenderSystem( HINSTANCE hInstance )
				: hInstance( hInstance )
		{
		}

		DirectX10RenderSystem::~DirectX10RenderSystem()
		{
			// TODO Auto-generated destructor stub
		}

		RenderWindow* DirectX10RenderSystem::createRenderWindow( const RenderWindowDesc& windowDesc )
		{
			return new DirectX10RenderWindow(windowDesc, this);
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
