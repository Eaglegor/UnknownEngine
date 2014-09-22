#pragma once

#include <unordered_map>

#include <InputContextMapperDescriptor.h>
#include <InputContextMapperCreationOptions.h>
#include <EngineContext.h>
#include <LogHelper.h>
#include <Exception.h>

#include <InputContext.h>
#include "EventHandlers/Keyboard/KeyboardEventHandler.h"

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
			void addSimpleAction(const AddSimpleActionMessage &msg);

        private:
            std::unique_ptr<Core::BaseMessageListener> listener;
            InputContextMapperCreationOptions creation_options;
			
			KeyboardEventHandler keyboard_event_handler;
			
			std::unordered_map<std::string, InputContext> contexts;
			
        };
    }
}