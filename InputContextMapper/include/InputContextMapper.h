#pragma once

#include <unordered_map>

#include <InputContextMapperDescriptor.h>
#include <InputContextMapperCreationOptions.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <Exception.h>

#include <InputContext.h>
#include <EventHandlers/KeyboardEventHandler.h>
#include <EventHandlers/MouseEventHandler.h>

namespace UnknownEngine
{

    namespace Core
    {
        class EngineContext;
        class LogHelper;
        class BaseMessageListener;
		struct UpdateFrameMessage;
    }

    namespace IO
    {

        struct KeyStateChangedMessage;
		struct AddSimpleActionMessage;
		struct AddRangeActionMessage;
		struct MouseWheelMovedMessage;
		struct MouseMovedMessage;
		struct MouseButtonStateChangedMessage;
		
        class InputContextMapper
        {
        public:
			
			UNKNOWNENGINE_SIMPLE_EXCEPTION(InputContextNotFoundException);
			UNKNOWNENGINE_SIMPLE_EXCEPTION(ActionSlotNotFoundException);
			
            InputContextMapper(const InputContextMapperDescriptor& desc, const InputContextMapperCreationOptions& creation_options);
			virtual ~InputContextMapper();

			InputContext* createContext(const std::string &name);
			InputContext* findContext(const std::string& name);
			
            void update(const Core::UpdateFrameMessage &msg);
            void onKeyPressed(const KeyStateChangedMessage &msg);
			
			void onMouseButtonClick(const MouseButtonStateChangedMessage& msg);
			void onMouseMoved(const MouseMovedMessage &msg);
			void onMouseWheelMoved(const MouseWheelMovedMessage &msg);
			
			void addSimpleAction(const AddSimpleActionMessage &msg);
			void addRangeAction(const AddRangeActionMessage &msg);

        private:
            std::unique_ptr<Core::BaseMessageListener> listener;
            InputContextMapperCreationOptions creation_options;
			
			KeyboardEventHandler keyboard_event_handler;
			MouseEventHandler mouse_event_handler;
			
			std::unordered_map<std::string, InputContext> contexts;
			
        };
    }
}