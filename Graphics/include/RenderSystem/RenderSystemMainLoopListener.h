#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <MainLoop/IMainLoopEventListener.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class RenderSystem;

		class RenderSystemMainLoopListener: public Core::IMainLoopEventListener
		{
			public:
				RenderSystemMainLoopListener (RenderSystem* render_system);
				virtual ~RenderSystemMainLoopListener ();

				virtual void onEvent ( const Core::MainLoopEvent &event );

			private:
				RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
