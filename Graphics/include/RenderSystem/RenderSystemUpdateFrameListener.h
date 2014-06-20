#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/IMessageListener.h>
#include <InlineSpecification.h>
#include <MessageSystem/Message.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class RenderSystem;

		class RenderSystemUpdateFrameListener: public Core::IMessageListener
		{
			public:
				RenderSystemUpdateFrameListener ( RenderSystem* render_system );
				virtual ~RenderSystemUpdateFrameListener ();

				UNKNOWNENGINE_INLINE
				virtual std::string getName () const
				{
					return render_system->getName ();
				}

				virtual void processMessage ( const Core::PackedMessage &msg );

			private:
				RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
