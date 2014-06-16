/*
 * DirectX10RenderWindow.cpp
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include "DirectX10RenderWindow.h"

namespace UnknownEngine
{
	namespace Graphics
	{

		DirectX10RenderWindow::DirectX10RenderWindow( const RenderWindowDesc &desc, const DirectX10RenderSystem* render_system )
				: render_system(render_system)
		{
		}

		DirectX10RenderWindow::~DirectX10RenderWindow()
		{
			// TODO Auto-generated destructor stub
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
