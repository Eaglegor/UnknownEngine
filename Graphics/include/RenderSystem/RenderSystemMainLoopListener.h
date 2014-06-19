#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class RenderSystem;
		class Message;

		class RenderSystemMainLoopListener: public Core::IMessageListener
		{
			public:
				RenderSystemMainLoopListener (RenderSystem* render_system);
				virtual ~RenderSystemMainLoopListener ();

				virtual void processMessage ( const Message &msg );

			private:
				RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
