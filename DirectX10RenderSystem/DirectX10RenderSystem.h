#pragma once

/*
 * DirectX10RenderSystem.h
 *
 *  Created on: 16 ���� 2014 �.
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
