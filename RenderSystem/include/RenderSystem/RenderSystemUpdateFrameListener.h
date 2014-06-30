#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <InlineSpecification.h>
#include <MessageSystem/IMessageListener.h>

namespace UnknownEngine
{

	namespace Core
	{
		class PackedMessage;
	}

	namespace Graphics
	{

		class RenderSystem;

		class RenderSystemUpdateFrameListener: public Core::IMessageListener
		{
			public:
				RenderSystemUpdateFrameListener ( RenderSystem* render_system );
				virtual ~RenderSystemUpdateFrameListener ();
				virtual void processMessage ( const Core::PackedMessage &msg ) override;

			private:
				RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
