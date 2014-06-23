#pragma once

/*
 * RenderWindowDesc.h

 *
 *  Created on: 16 июня 2014 г.
 *      Author: Eaglegor
 */

#include <string>

#include <UnknownEngineString.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		struct RenderWindowDesc
		{
			int width;
			int height;
			String title;
			bool fullscreen;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
