#pragma once

#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
    namespace IO
    {
        struct InputContextMapperDescriptor
        {
            Core::LogMessage::Severity log_level;

            InputContextMapperDescriptor():
            log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
            {}
        };
    }
}