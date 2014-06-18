#pragma once
/*
 * MainLoopEvent.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace Core
	{

		class MainLoopEvent
		{
			public:
				MainLoopEvent (float dt);
				virtual ~MainLoopEvent ();

				UNKNOWNENGINE_INLINE
				float getDeltaTime(){return dt;}

			private:
				float dt;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
