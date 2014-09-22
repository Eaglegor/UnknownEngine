#include <InputContextMapper.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
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
				typedef AddSimpleActionMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::addSimpleAction);
				listener->registerMessageBuffer(buffer);
			}

			{
				typedef IO::KeyStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onKeyPressed);
				listener->registerMessageBuffer(buffer);
			}

			InputContext* context = createContext("Generic");
			context->createSimpleActionSlot("StopEngine", SimpleActionSlot::ConditionType::EVENT_STARTED);
			keyboard_event_handler.addActionSlotSubscription("Generic", "StopEngine", Key::ESCAPE);

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
		
		void InputContextMapper::addSimpleAction(const AddSimpleActionMessage &msg)
		{
			InputContext* context = findContext(msg.context_name);
			if(context == nullptr) throw InputContextNotFoundException("Can't find requested input context: " + msg.context_name);
			SimpleActionSlot* action_slot = context->findSimpleActionSlot(msg.action_slot_name);
			if(action_slot == nullptr) throw ActionSlotNotFoundException("Can't find requested action slot: " + msg.action_slot_name);
			action_slot->setAction(msg.action_callback);
		}
		
	}
}