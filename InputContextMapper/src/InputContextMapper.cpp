#include <InputContextMapper.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <MessageSystem/BaseMessageListener.h>
#include <Listeners/BaseMessageListenersFactory.h>
#include <Listeners/StandardMessageBuffersFactory.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageBuffers/QueuedMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseButtonStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseMovedMessage.h>
#include <ExportedMessages/UserInput/MouseWheelMovedMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

namespace UnknownEngine
{
	namespace IO
	{
		InputContextMapper::InputContextMapper(const InputContextMapperDescriptor &desc, const InputContextMapperCreationOptions &creation_options):
		creation_options(creation_options),
		keyboard_event_handler(this),
		mouse_event_handler(this)
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
				typedef AddRangeActionMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::addRangeAction);
				listener->registerMessageBuffer(buffer);
			}
			
			{
				typedef IO::KeyStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;

				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onKeyPressed);
				listener->registerMessageBuffer(buffer);
			}

			{
				typedef IO::MouseButtonStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onMouseButtonClick);
				listener->registerMessageBuffer(buffer);
			}
			
			{
				typedef IO::MouseMovedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onMouseMoved);
				listener->registerMessageBuffer(buffer);
			}
			
			{
				typedef IO::MouseWheelMovedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				BufferType buffer = factory.createBuffer<BufferType>(&InputContextMapper::onMouseWheelMoved);
				listener->registerMessageBuffer(buffer);
			}
			
			InputContext* context = createContext("Generic");
			context->createSimpleActionSlot("StopEngine", SimpleActionSlot::ConditionType::EVENT_STARTED);
			keyboard_event_handler.addActionSlotSubscription("Generic", "StopEngine", Key::ESCAPE);
			
			context = createContext("MouseLook");
			context->createSimpleActionSlot("MoveForward", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			context->createSimpleActionSlot("MoveBackward", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			context->createSimpleActionSlot("StrafeLeft", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			context->createSimpleActionSlot("StrafeRight", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			context->createSimpleActionSlot("StrafeUp", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			context->createSimpleActionSlot("StrafeDown", SimpleActionSlot::ConditionType::EVENT_ACTIVE);
			
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "MoveForward", Key::W);
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "MoveBackward", Key::S);
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "StrafeLeft", Key::A);
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "StrafeRight", Key::D);
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "StrafeUp", Key::E);
			keyboard_event_handler.addActionSlotSubscription("MouseLook", "StrafeDown", Key::Q);
			
			context->createRangeActionSlot("Pitch");
			context->createRangeActionSlot("Yaw");
			
			mouse_event_handler.addActionSlotSubscription("MouseLook", "Pitch", MouseAxis::Y);
			mouse_event_handler.addActionSlotSubscription("MouseLook", "Yaw", MouseAxis::X);
			
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
		
		void InputContextMapper::addRangeAction(const AddRangeActionMessage &msg)
		{
			InputContext* context = findContext(msg.context_name);
			if(context == nullptr) throw InputContextNotFoundException("Can't find requested input context: " + msg.context_name);
			RangeActionSlot* action_slot = context->findRangeActionSlot(msg.action_slot_name);
			if(action_slot == nullptr) throw ActionSlotNotFoundException("Can't find requested action slot: " + msg.action_slot_name);
			action_slot->setAction(msg.action_callback);
		}
		
		void InputContextMapper::onMouseButtonClick ( const MouseButtonStateChangedMessage& msg )
		{
			mouse_event_handler.processEvent(msg.button_id, msg.new_state);
		}

		void InputContextMapper::onMouseMoved ( const MouseMovedMessage& msg )
		{
			mouse_event_handler.processEvent(MouseAxis::X, msg.delta_x);
			mouse_event_handler.processEvent(MouseAxis::Y, msg.delta_y);
		}

		void InputContextMapper::onMouseWheelMoved ( const MouseWheelMovedMessage& msg )
		{
			std::cout << "Mouse wheel found" << std::endl;
			mouse_event_handler.processEvent(MouseAxis::Z, msg.delta_y);
		}

	}
}