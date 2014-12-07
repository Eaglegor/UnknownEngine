#pragma once

#include <string>

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
            Core::EngineContext* engine_context;
            Core::ILogger* logger;
        };
    }
}