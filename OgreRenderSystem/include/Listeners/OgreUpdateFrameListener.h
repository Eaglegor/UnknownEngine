#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		class OgreRenderSubsystem;
		
		class OgreUpdateFrameListener: public Core::IMessageListener
		{
			public:
				OgreUpdateFrameListener ( const std::string &name, OgreRenderSubsystem* render_system );
				void processMessage ( const Core::PackedMessage &msg ) override;
				virtual const char* getName() const;

			private:
				const std::string name;
				OgreRenderSubsystem* render_system;
		};

	} // namespace Graphics
} // namespace UnknownEngine
