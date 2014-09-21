#pragma once

#include <unordered_map>

#include <InputContextMapperDescriptor.h>
#include <InputContextMapperCreationOptions.h>
#include <EngineContext.h>
#include <LogHelper.h>

#include <InputContext.h>

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

        class InputContextMapper
        {
        public:
            InputContextMapper(const InputContextMapperDescriptor& desc, const InputContextMapperCreationOptions& creation_options);
			virtual ~InputContextMapper();

            void update(const Core::UpdateFrameMessage &msg);
            void onKeyPressed(const KeyStateChangedMessage& msg);

        private:
            std::unique_ptr<Core::BaseMessageListener> listener;
            InputContextMapperCreationOptions creation_options;
			
			InputContext context;
			
        };
    }
}