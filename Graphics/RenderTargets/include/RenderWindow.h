#pragma once

/*
 * RenderWindow.h
 *
 *  Created on: 15 ���� 2014 �.
 *      Author: Eaglegor
 */

#include "RenderWindowDesc.h"

namespace UnknownEngine
{
	namespace Graphics
	{

		class RenderWindow
		{
			public:
				virtual ~RenderWindow ()
				{
				}

			protected:
				RenderWindow ( const RenderWindowDesc &desc )
				{
				}

		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
