#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 ���� 2014 �.
 *      Author: gorbachenko
 */

#include <MessageSystem/IMessageListener.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{

	namespace Core{
		class Message;
	}

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

				virtual void processMessage ( const Core::Message &msg );

			private:
				RenderSystem* render_system;
		};

	} /* namespace Graphics */
} /* namespace UnknownEngine */
