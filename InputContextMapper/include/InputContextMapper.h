#pragma once

#include <unordered_map>

#include <InputContextMapperDescriptor.h>
#include <InputContextMapperCreationOptions.h>
#include <EngineContext.h>
#include <Exception.h>

#include <InputContext.h>
#include <EventHandlers/KeyboardEventHandler.h>
#include <EventHandlers/MouseEventHandler.h>
#include <EventHandlers/JoystickEventHandler.h>

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>

#include <ComponentSystem/BaseComponent.h>

#include <ComponentInterfaces/Input/Common/IMouseHandler.h>
#include <ComponentInterfaces/Input/Common/IKeyboardHandler.h>
#include <ComponentInterfaces/Input/Common/IJoystickHandler.h>

#include <ComponentInterfaces/Input/Common/IMouseEventsListener.h>
#include <ComponentInterfaces/Input/Common/IKeyboardEventsListener.h>
#include <ComponentInterfaces/Input/Common/IJoystickEventsListener.h>

#include <ComponentInterfaces/Input/Common/IContextualActionsMapper.h>

#include <ComponentSystem/ComponentInterfacePtr.h>

#include <LogHelper.h>

namespace UnknownEngine
{

    namespace Core
    {
        class BaseMessageListener;
		class ILogger;
    }

    namespace IO
    {
        class InputContextMapper : 
			public Core::BaseComponent,
			public ComponentInterfaces::UpdateFrameListenerComponent,
			public ComponentInterfaces::IMouseEventsListener,
			public ComponentInterfaces::IKeyboardEventsListener,
			public ComponentInterfaces::IJoystickEventsListener,
			public ComponentInterfaces::IContextualActionsMapper
        {
        public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(InputContextNotFoundException);
			UNKNOWNENGINE_SIMPLE_EXCEPTION(ActionSlotNotFoundException);
			
            InputContextMapper(const char* name, const InputContextMapperDescriptor& desc);
			virtual ~InputContextMapper();

			InputContext* createContext(const std::string &name);
			InputContext* findContext(const std::string& name);
			
			constexpr static const char* getTypeName(){return "InputContextMapper";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual bool init ();
			virtual void shutdown();
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
			virtual void onKeyboardEvent ( const KeyboardEvent& evt ) override;
			
			virtual void onMouseButtonEvent ( const MouseButtonEvent& evt ) override;
			virtual void onMouseMoveEvent ( const MouseMovedEvent& evt ) override;
			virtual void onMouseWheelEvent ( const MouseWheelEvent& evt ) override;
			
			virtual void onJoystickAxisEvent ( const JoystickAxisEvent& evt ) override;
			virtual void onJoystickButtonEvent ( const JoystickButtonEvent& evt ) override;
			
			virtual void addSimpleAction ( const char* context_name, const char* action_slot_name, std::function< void() > action_callback ) override;
			virtual void addRangedAction ( const char* context_name, const char* action_slot_name, std::function< void(Math::Scalar) > action_callback ) override;

			virtual void removeSimpleAction ( const char* context_name, const char* action_slot_name ) override;
			virtual void removeRangedAction ( const char* context_name, const char* action_slot_name ) override;
			
			virtual IComponentInterface* getInterface ( const Core::ComponentType& type );
			
			KeyboardEventHandler* getKeyboardEventHandler();
			MouseEventHandler* getMouseEventHandler();
			JoystickEventHandler* getJoystickEventHandler();
			
        private:
			InputContextMapperDescriptor desc;
			
			KeyboardEventHandler keyboard_event_handler;
			MouseEventHandler mouse_event_handler;
			JoystickEventHandler joystick_event_handler;
			
			std::unordered_map<std::string, InputContext> contexts;
			
			Core::LogHelper logger;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::IMouseHandler> mouse_input_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::IKeyboardHandler> keyboard_input_provider;
			Core::ComponentInterfacePtr<ComponentInterfaces::IJoystickHandler> joystick_input_provider;
			
        };
    }
}