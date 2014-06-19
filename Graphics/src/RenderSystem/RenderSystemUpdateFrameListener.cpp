/*
 * RenderSystemMainLoopListener.cpp

 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderSystemUpdateFrameListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		RenderSystemUpdateFrameListener::RenderSystemUpdateFrameListener ( RenderSystem* render_system )
				: render_system ( render_system )
		{
		}

		RenderSystemUpdateFrameListener::~RenderSystemUpdateFrameListener ()
		{
		}

		void RenderSystemUpdateFrameListener::processMessage (  const Core::Message &msg )
		{
			this->render_system->renderFrame();
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
