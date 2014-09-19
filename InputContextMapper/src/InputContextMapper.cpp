#include <InputContextMapper.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/StandardMessageBuffersFactory.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageBuffers/QueuedMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine
{
	namespace IO
	{
		InputContextMapper::InputContextMapper(const InputContextMapperDescriptor &desc, const InputContextMapperCreationOptions &creation_options)
				: creation_options(creation_options)
		{
			listener = std::move(Utils::BaseMessageListenersFactory::createBaseMessageListener(creation_options.name, creation_options.engine_context, creation_options.received_messages));

			Utils::StandardMessageBuffersFactory<InputContextMapper> factory(this);

			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::update);
				listener->registerMessageBuffer(buffer);
			}

			{
				typedef IO::KeyStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onKeyPressed);
				listener->registerMessageBuffer(buffer);
			}

		}

		InputContextMapper::~InputContextMapper(){};

		void InputContextMapper::update(const Core::UpdateFrameMessage& msg)
		{
			listener->flushAllMessageBuffers();
		}

		void InputContextMapper::onKeyPressed(const KeyStateChangedMessage &msg)
		{
			switch(msg.new_state)
			{
				case KeyState::KEY_PRESSED:
				{
					LOG_DEBUG(creation_options.log_helper, "Processing key press: " + std::to_string(static_cast<int>(msg.key)));



					break;
				}
				case KeyState::KEY_UNPRESSED:
				{
					LOG_DEBUG(creation_options.log_helper, "Processing key release: " + std::to_string(static_cast<int>(msg.key)));



					break;
				}
			}
		}
	}
}