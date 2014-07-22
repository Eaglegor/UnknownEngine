#pragma once

#include <MessageSystem/IMessageListener.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine {
	namespace Graphics {

		class OgreRenderSubsystem;

		class OgreUpdateFrameListener: public Core::IMessageListener
		{
			public:
				OgreUpdateFrameListener(const std::string &name, OgreRenderSubsystem* render_system);
				void processMessage(const Core::PackedMessage &msg);

			private:
				OgreRenderSubsystem* render_system;
				Core::UpdateFrameMessageUnpacker message_unpacker;
		};

	} // namespace Graphics
} // namespace UnknownEngine
