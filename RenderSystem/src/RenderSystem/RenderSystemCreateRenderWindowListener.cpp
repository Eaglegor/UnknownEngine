/*
 * RenderSystemMainLoopListener.cpp

 *
 *  Created on: 17 июня 2014 г.
 *      Author: gorbachenko
 */

#include <stdafx.h>

#include <RenderSystem/RenderSystem.h>
#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>
#include <RenderSystem/RenderSystemCreateRenderWindowListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		RenderSystemCreateRenderWindowListener::RenderSystemCreateRenderWindowListener ( RenderSystem* render_system )
				: render_system ( render_system ),
				  IMessageListener ( Core::MessageSystemId( render_system->getName()) )
		{
		}

		RenderSystemCreateRenderWindowListener::~RenderSystemCreateRenderWindowListener ()
		{
		}

		void RenderSystemCreateRenderWindowListener::processMessage (  const Core::PackedMessage &msg )
		{
			CreateRenderWindowMessage unpacked_msg = CreateRenderWindowMessageUnpacker().unpackMessage(msg);
			this->render_system->createRenderWindow(unpacked_msg.window_desc);
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
