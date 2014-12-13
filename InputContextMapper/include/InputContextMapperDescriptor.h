#pragma once

#include <LogSeverity.h>
#include <string>

namespace UnknownEngine
{
    namespace IO
    {
        struct InputContextMapperDescriptor
        {
            Core::LogSeverity log_level;
			
			std::string action_slots_config_file;
			std::string input_layout_config_file;

			
            InputContextMapperDescriptor():
            log_level(Core::LogSeverity::NONE)
            {}
        };
    }
}