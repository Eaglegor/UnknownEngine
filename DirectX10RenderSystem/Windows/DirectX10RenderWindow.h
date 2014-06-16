#pragma once

/*
 * DirectX10RenderWindow.h
 *
 *  Created on: 16 ���� 2014 �.
 *      Author: Eaglegor
 */

#include <RenderWindow.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX10RenderWindow: public RenderWindow
		{
			public:
				DirectX10RenderWindow (const RenderWindowDesc &desc);
				virtual ~DirectX10RenderWindow ();
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
