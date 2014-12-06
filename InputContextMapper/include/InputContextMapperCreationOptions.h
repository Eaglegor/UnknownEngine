#pragma once

#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{
    namespace Core
    {
        class EngineContext;
		class ILogger;
    }

    namespace IO
    {
        struct InputContextMapperCreationOptions
        {
            std::string name;
            Core::ReceivedMessageDescriptorsList received_messages;
            Core::EngineContext* engine_context;
            Core::ILogger* logger;
        };
    }
}