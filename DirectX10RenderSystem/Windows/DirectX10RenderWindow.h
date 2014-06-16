#pragma once

/*
 * DirectX10RenderWindow.h
 *
 *  Created on: 16 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#include <RenderWindow.h>

class DirectX10RenderSystem;

namespace UnknownEngine
{
	namespace Graphics
	{

		class DirectX10RenderWindow: public RenderWindow
		{
			public:
				DirectX10RenderWindow (const RenderWindowDesc &desc, const DirectX10RenderSystem *render_system );
				virtual ~DirectX10RenderWindow ();
			private:
				const DirectX10RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
