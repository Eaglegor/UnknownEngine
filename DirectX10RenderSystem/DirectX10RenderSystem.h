#pragma once

/*
 * DirectX10RenderSystem.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <RenderSystem.h>
#include <RenderWindow.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX10RenderSystem: public RenderSystem
		{
			public:
				DirectX10RenderSystem ();
				virtual ~DirectX10RenderSystem ();

				RenderWindow* createRenderWindow(const RenderWindowDesc &windowDesc);
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
