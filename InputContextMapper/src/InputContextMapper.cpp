#include <stdafx.h>
#include <InputContextMapper.h>
#include <Parsers/ActionSlotsConfigParser.h>
#include <Parsers/InputLayoutConfigParser.h>

#include <Logging.h>

namespace UnknownEngine
{
	namespace IO
	{
		InputContextMapper::InputContextMapper(const char* name, const InputContextMapperDescriptor& desc):
		Core::BaseComponent(name),
		desc(desc),
		keyboard_event_handler(this),
		mouse_event_handler(this),
		joystick_event_handler(this),
		logger(name, desc.log_level),
		update_frame_provider(desc.update_frame_provider),
		mouse_input_provider(desc.mouse_input_provider),
		keyboard_input_provider(desc.keyboard_input_provider),
		joystick_input_provider(desc.joystick_input_provider)
		{
		}

		InputContextMapper::~InputContextMapper(){
		};

		void InputContextMapper::init ( const Core::IEntity* parent_entity )
		{
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
			
			joystick_event_handler.setJoystickAxisValueMapping(-32768, 32767, -1, 1);
			
			if(update_frame_provider) update_frame_provider->addListener(this);
			if(keyboard_input_provider) keyboard_input_provider->addKeyboardEventsListener(this);
			if(mouse_input_provider) mouse_input_provider->addMouseEventsListener(this);
			if(joystick_input_provider) joystick_input_provider->addJoystickEventsListener(this);
		}

		void InputContextMapper::shutdown()
		{
			if(joystick_input_provider) joystick_input_provider->removeJoystickEventsListener(this);
			if(mouse_input_provider) mouse_input_provider->removeMouseEventsListener(this);
			if(keyboard_input_provider) keyboard_input_provider->removeKeyboardEventsListener(this);
			if(update_frame_provider) update_frame_provider->removeListener(this);
		}
		
		void InputContextMapper::onUpdateFrame ( Math::Scalar dt )
		{
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

		void InputContextMapper::addSimpleAction ( const char* context_name, const char* action_slot_name, std::function< void() > action_callback )
		{
			LOG_INFO(logger, "Registering simple action. Context: " + context_name + ", Slot: " + action_slot_name);
			InputContext* context = findContext(context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + std::string(context_name));
			}
			SimpleActionSlot* action_slot = context->findSimpleActionSlot(action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + std::string(action_slot_name));
			}
			action_slot->setAction(action_callback);
		}
		
		void InputContextMapper::addRangedAction ( const char* context_name, const char* action_slot_name, std::function< void(Math::Scalar) > action_callback )
		{
			LOG_INFO(logger, "Registering range action. Context: " + context_name + ", Slot: " + action_slot_name);
			InputContext* context = findContext(context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + std::string(context_name));
			}
			RangeActionSlot* action_slot = context->findRangeActionSlot(action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + std::string(action_slot_name));
			}
			action_slot->setAction(action_callback);
		}

		void InputContextMapper::removeSimpleAction ( const char* context_name, const char* action_slot_name )
		{
			LOG_INFO(logger, "Removing simple action. Context: " + context_name + ", Slot: " + action_slot_name);
			InputContext* context = findContext(context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + std::string(context_name));
			}
			SimpleActionSlot* action_slot = context->findSimpleActionSlot(action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + std::string(action_slot_name));
			}
			action_slot->reset();
		}

		void InputContextMapper::removeRangedAction ( const char* context_name, const char* action_slot_name )
		{
			LOG_INFO(logger, "Removing range action. Context: " + context_name + ", Slot: " + action_slot_name);
			InputContext* context = findContext(context_name);
			if(context == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested input context: " + context_name);
				throw InputContextNotFoundException("Can't find requested input context: " + std::string(context_name));
			}
			RangeActionSlot* action_slot = context->findRangeActionSlot(action_slot_name);
			if(action_slot == nullptr) 
			{
				LOG_ERROR(logger, "Can't find requested action slot: " + action_slot_name);
				throw ActionSlotNotFoundException("Can't find requested action slot: " + std::string(action_slot_name));
			}
			action_slot->reset();
		}

		
		void InputContextMapper::onMouseButtonEvent ( const MouseButtonEvent& evt )
		{
			mouse_event_handler.processEvent(evt.button_id, evt.new_state);
		}

		void InputContextMapper::onMouseMoveEvent ( const MouseMovedEvent& evt )
		{
			mouse_event_handler.processEvent(MouseAxis::X, evt.delta_x);
			mouse_event_handler.processEvent(MouseAxis::Y, evt.delta_y);
		}

		void InputContextMapper::onMouseWheelEvent ( const MouseWheelEvent& evt )
		{
			mouse_event_handler.processEvent(MouseAxis::Z, evt.delta);
		}

		void InputContextMapper::onJoystickAxisEvent ( const JoystickAxisEvent& evt )
		{
			joystick_event_handler.processEvent(evt.joystick_id, evt.axis_id, evt.new_value);
		}

		void InputContextMapper::onJoystickButtonEvent ( const JoystickButtonEvent& evt )
		{
			joystick_event_handler.processEvent(evt.joystick_id, evt.button_id, evt.new_state);
		}
		
		void InputContextMapper::onKeyboardEvent ( const KeyboardEvent& evt )
		{
			keyboard_event_handler.processEvent(evt.key, evt.new_state);
		}
		
		KeyboardEventHandler* InputContextMapper::getKeyboardEventHandler()
		{
			return &keyboard_event_handler;
		}
		
		MouseEventHandler* InputContextMapper::getMouseEventHandler()
		{
			return &mouse_event_handler;
		}
		
		JoystickEventHandler* InputContextMapper::getJoystickEventHandler()
		{
			return &joystick_event_handler;
		}
		
		Core::IComponentInterface* InputContextMapper::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::IContextualActionsMapper::getTypeName()) return static_cast<ComponentInterfaces::IContextualActionsMapper*>(this);
			return nullptr;
		}
	
	}
}