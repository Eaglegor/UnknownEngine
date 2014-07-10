/*
 * RenderSystemMainLoopListener.cpp

 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderSystemUpdateFrameListener.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		RenderSystemUpdateFrameListener::RenderSystemUpdateFrameListener ( RenderSystem* render_system )
				: render_system ( render_system ),
				  Core::IMessageListener( render_system->getName() )
		{
		}

		RenderSystemUpdateFrameListener::~RenderSystemUpdateFrameListener ()
		{
		}

		void RenderSystemUpdateFrameListener::processMessage (  const Core::PackedMessage &msg )
		{
			if(Core::UpdateFrameMessageUnpacker().unpackMessage(msg).stage == Core::UpdateFrameMessage::PROCESSING)
			{
				this->render_system->renderFrame();
			}
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
