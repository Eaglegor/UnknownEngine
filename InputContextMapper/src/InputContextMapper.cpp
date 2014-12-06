#include <stdafx.h>
#include <InputContextMapper.h>
#include <ExportedMessages/InputContext/AddSimpleActionMessage.h>
#include <ExportedMessages/InputContext/AddRangeActionMessage.h>
#include <Parsers/ActionSlotsConfigParser.h>
#include <Parsers/InputLayoutConfigParser.h>
#include <MessageSystem/BaseMessageListener.h>
#include <ExportedMessages/UpdateFrameMessage.h>
#include <MessageBuffers/QueuedMessageBuffer.h>
#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <ExportedMessages/UserInput/KeyStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseButtonStateChangedMessage.h>
#include <ExportedMessages/UserInput/MouseMovedMessage.h>
#include <ExportedMessages/UserInput/MouseWheelMovedMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

#include <Logging.h>

namespace UnknownEngine
{
	namespace IO
	{
		InputContextMapper::InputContextMapper( const InputContextMapperDescriptor& desc, const InputContextMapperCreationOptions& creation_options, Core::ILogger* logger ):
		creation_options(creation_options),
		keyboard_event_handler(this),
		mouse_event_handler(this),
		logger(logger)
		{
			listener.reset(new Core::BaseMessageListener(creation_options.name, creation_options.engine_context));
			listener->registerSupportedMessageTypes(creation_options.received_messages);

			LOG_INFO(logger, "Registering update frame message buffer");
			{
				typedef Core::UpdateFrameMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::update);
			}
			
			LOG_INFO(logger, "Registering add simple action message buffer");
			{
				typedef AddSimpleActionMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::addSimpleAction);
			}

			LOG_INFO(logger, "Registering add range action message buffer");
			{
				typedef AddRangeActionMessage MessageType;
				typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;

				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::addRangeAction);
			}
			
			LOG_INFO(logger, "Registering on key pressed message buffer");
			{
				typedef IO::KeyStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;

				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::onKeyPressed);
			}

			LOG_INFO(logger, "Registering on mouse button click message buffer");
			{
				typedef IO::MouseButtonStateChangedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::onMouseButtonClick);
			}
			
			LOG_INFO(logger, "Registering on mouse moved message buffer");
			{
				typedef IO::MouseMovedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::onMouseMoved);
			}
			
			LOG_INFO(logger, "Registering on mouse wheel moved message buffer");
			{
				typedef IO::MouseWheelMovedMessage MessageType;
				typedef Utils::QueuedMessageBuffer<MessageType> BufferType;
				
				listener->createMessageBuffer<MessageType, BufferType>(this, &InputContextMapper::onMouseWheelMoved);
			}
			
			if(!desc.action_slots_config_file.empty())
			{
				LOG_INFO(logger, "Parsing action slots config file");
				ActionSlotsConfigParser parser(this, logger);
				parser.processConfig(desc.action_slots_config_file);
			}
			else
			{
				LOG_WARNING(logger, "Action slots description file is not set. There will be no action contexts and slots.");
			}
			
			if(!desc.input_layout_config_file.empty())
			{
				LOG_INFO(logger, "Parsing input layout config file");
				InputLayoutConfigParser parser(this, logger);
				parser.processConfig(desc.input_layout_config_file);
			}
			
			LOG_INFO(logger, "Registering listener");
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
			LOG_INFO(logger, "Creating input context: " + name);
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
			LOG_INFO(logger, "Registering simple action. Context: " + msg.context_name + ", Slot: " + msg.action_slot_name);
			InputContext* context = findContext(msg.context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + msg.context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + msg.context_name);
			}
			SimpleActionSlot* action_slot = context->findSimpleActionSlot(msg.action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + msg.action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + msg.action_slot_name);
			}
			action_slot->setAction(msg.action_callback);
		}
		
		void InputContextMapper::addRangeAction(const AddRangeActionMessage &msg)
		{
			LOG_INFO(logger, "Registering range action. Context: " + msg.context_name + ", Slot: " + msg.action_slot_name);
			InputContext* context = findContext(msg.context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + msg.context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + msg.context_name);
			}
			RangeActionSlot* action_slot = context->findRangeActionSlot(msg.action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + msg.action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + msg.action_slot_name);
			}
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

		KeyboardEventHandler* InputContextMapper::getKeyboardEventHandler()
		{
			return &keyboard_event_handler;
		}
		
		MouseEventHandler* InputContextMapper::getMouseEventHandler()
		{
			return &mouse_event_handler;
		}
		
	}
}