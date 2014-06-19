#pragma once
/*
 * RenderSystemMainLoopListener.h
 *
 *  Created on: 17 θώνÿ 2014 γ.
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

		class RenderSystemMainLoopListener: public Core::IMessageListener
		{
			public:
				RenderSystemMainLoopListener ( RenderSystem* render_system );
				virtual ~RenderSystemMainLoopListener ();

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
