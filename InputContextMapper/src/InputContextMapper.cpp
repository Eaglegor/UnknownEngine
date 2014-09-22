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
		InputContextMapper::InputContextMapper(const InputContextMapperDescriptor &desc, const InputContextMapperCreationOptions &creation_options):
		creation_options(creation_options),
		keyboard_event_handler(this)
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

			InputContext* context = createContext("Test");
			
			SimpleActionSlot* action_slot = context->createSimpleActionSlot("KeyDown", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			action_slot->setAction([](){std::cout << "Key is down" << std::endl;});
			keyboard_event_handler.addActionSlotSubscription("Test", "KeyDown", Key::T);
			
			action_slot = context->createSimpleActionSlot("KeyPressed", SimpleActionSlot::ConditionType::EVENT_STARTED);
			action_slot->setAction([](){std::cout << "Key pressed" << std::endl;});
			keyboard_event_handler.addActionSlotSubscription("Test", "KeyPressed", Key::W);
			
			action_slot = context->createSimpleActionSlot("KeyReleased", SimpleActionSlot::ConditionType::EVENT_ENDED);
			action_slot->setAction([](){std::cout << "Key released" << std::endl;});
			keyboard_event_handler.addActionSlotSubscription("Test", "KeyReleased", Key::S);
			
			listener->registerAtDispatcher();
			
		}

		InputContextMapper::~InputContextMapper(){
			listener->unregisterAtDispatcher();
		};

		void InputContextMapper::update(const Core::UpdateFrameMessage& msg)
		{
			listener->flushAllMessageBuffers();
			for(auto &iter : contexts)
			{
				iter.second.update();
			}
		}

		InputContext* InputContextMapper::createContext(const std::string& name)
		{
			return &(contexts.emplace(name, InputContext()).first->second);
		}
		
		InputContext* InputContextMapper::findContext(const std::string& name)
		{
			auto iter = contexts.find(name);
			if(iter == contexts.end()) return nullptr;
			return &iter->second;
		}
		
		void InputContextMapper::onKeyPressed(const KeyStateChangedMessage &msg)
		{
			keyboard_event_handler.processEvent(msg.key, msg.new_state);
		}
	}
}