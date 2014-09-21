#include <InputContextMapper.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/StandardMessageBuffersFactory.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageBuffers/QueuedMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <KeyIsDownCondition.h>
#include <ActionSlot.h>

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

			
			std::unique_ptr<ActionSlot> test_action_slot(new ActionSlot());
			std::unique_ptr<ActionCondition> condition(new KeyIsDownCondition(Key::T));
			test_action_slot->setCondition(std::move(condition));
			
			test_action_slot->setAction([](){ std::cout << "Key is down!" << std::endl; });
			
			context.addActionSlot("Test", std::move(test_action_slot));
			
			listener->registerAtDispatcher();
			
		}

		InputContextMapper::~InputContextMapper(){
			listener->unregisterAtDispatcher();
		};

		void InputContextMapper::update(const Core::UpdateFrameMessage& msg)
		{
			listener->flushAllMessageBuffers();
			context.update();
		}

		void InputContextMapper::onKeyPressed(const KeyStateChangedMessage &msg)
		{
			context.processEvent(msg.key, msg.new_state);
		}
	}
}