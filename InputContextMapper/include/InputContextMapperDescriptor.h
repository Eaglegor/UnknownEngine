#pragma once

#include <ExportedMessages/LogMessage.h>

namespace UnknownEngine
{
    namespace IO
    {
        struct InputContextMapperDescriptor
        {
            Core::LogMessage::Severity log_level;
			
			std::string action_slots_config_file;
			std::string input_layout_config_file;

            InputContextMapperDescriptor():
            log_level(Core::LogMessage::Severity::LOG_SEVERITY_NONE)
            {}
        };
    }
}