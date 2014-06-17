/*
 * RenderSystemMainLoopListener.cpp

 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderSystemMainLoopListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		RenderSystemMainLoopListener::RenderSystemMainLoopListener ( RenderSystem* render_system )
				: render_system ( render_system )
		{
		}

		RenderSystemMainLoopListener::~RenderSystemMainLoopListener ()
		{
		}

		void RenderSystemMainLoopListener::onEvent ( const Core::MainLoopEvent& event )
		{
			this->render_system->renderFrame();
		}

	} /* namespace Graphics */
} /* namespace UnknownEngine */
