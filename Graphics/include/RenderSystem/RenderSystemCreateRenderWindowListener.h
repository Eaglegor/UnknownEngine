#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
 *      Author: gorbachenko
 */

#include <MessageSystem/IMessageListener.h>
#include <InlineSpecification.h>
#include <MessageSystem/PackedMessage.h>

namespace UnknownEngine
{

	namespace Graphics
	{

		class RenderSystem;

		class RenderSystemCreateRenderWindowListener: public Core::IMessageListener
		{
			public:
				RenderSystemCreateRenderWindowListener ( RenderSystem* render_system );
				virtual ~RenderSystemCreateRenderWindowListener ();

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
