/*
 * RenderSystemMainLoopListener.cpp

 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */
#include <RenderSystem/RenderSystem.h>
#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>
#include <RenderSystem/RenderSystemCreateRenderWindowListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		RenderSystemCreateRenderWindowListener::RenderSystemCreateRenderWindowListener ( RenderSystem* render_system )
				: render_system ( render_system )
		{
		}

		RenderSystemCreateRenderWindowListener::~RenderSystemCreateRenderWindowListener ()
		{
		}

		void RenderSystemCreateRenderWindowListener::processMessage (  const Core::PackedMessage &msg )
		{
			CreateRenderWindowMessage unpacked_msg = CreateRenderWindowMessagePacker("").unpackMessage(msg);
			this->render_system->createRenderWindow(unpacked_msg.window_desc);
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
