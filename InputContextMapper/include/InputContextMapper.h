#pragma once

#include <unordered_map>

#include <InputContextMapperDescriptor.h>
#include <InputContextMapperCreationOptions.h>
#include <EngineContext.h>
#include <Exception.h>

#include <InputContext.h>
#include <EventHandlers/KeyboardEventHandler.h>
#include <EventHandlers/MouseEventHandler.h>
#include "EventHandlers/JoystickEventHandler.h"

#include <ComponentInterfaces/Engine/FrameUpdaterComponent.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>

namespace UnknownEngine
{

    namespace Core
    {
        class EngineContext;
        class BaseMessageListener;
		class ILogger;
    }

    namespace IO
    {

		struct JoystickAxisMovedMessage;
 		struct JoystickButtonStateChangedMessage;

        struct KeyStateChangedMessage;
		struct AddSimpleActionMessage;
		struct AddRangeActionMessage;
		struct MouseWheelMovedMessage;
		struct MouseMovedMessage;
		struct MouseButtonStateChangedMessage;
		
        class InputContextMapper : public ComponentInterfaces::UpdateFrameListenerComponent
        {
        public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(InputContextNotFoundException);
			UNKNOWNENGINE_SIMPLE_EXCEPTION(ActionSlotNotFoundException);
			
            InputContextMapper(const InputContextMapperDescriptor& desc, const InputContextMapperCreationOptions& creation_options, Core::ILogger *logger);
			virtual ~InputContextMapper();

			InputContext* createContext(const std::string &name);
			InputContext* findContext(const std::string& name);
			
			virtual void onUpdateFrame ( Math::Scalar dt ) override;
			
            void onKeyPressed(const KeyStateChangedMessage &msg);
			
			void onMouseButtonClick(const MouseButtonStateChangedMessage& msg);
			void onMouseMoved(const MouseMovedMessage &msg);
			void onMouseWheelMoved(const MouseWheelMovedMessage &msg);

			void onJoystickAxisMoved(const JoystickAxisMovedMessage &msg);
			void onJoystickButtonStateChanged(const JoystickButtonStateChangedMessage &msg);
			
			void addSimpleAction(const AddSimpleActionMessage &msg);
			void addRangeAction(const AddRangeActionMessage &msg);

			KeyboardEventHandler* getKeyboardEventHandler();
			MouseEventHandler* getMouseEventHandler();
			JoystickEventHandler* getJoystickEventHandler();
			
        private:
            std::unique_ptr<Core::BaseMessageListener> listener;
            InputContextMapperCreationOptions creation_options;
			
			KeyboardEventHandler keyboard_event_handler;
			MouseEventHandler mouse_event_handler;
			JoystickEventHandler joystick_event_handler;
			
			std::unordered_map<std::string, InputContext> contexts;
			
			Core::ILogger* logger;
			
			Core::ComponentInterfacePtr<ComponentInterfaces::FrameUpdaterComponent> update_frame_provider;
			
        };
    }
}