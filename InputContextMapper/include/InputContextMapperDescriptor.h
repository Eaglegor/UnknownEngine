#pragma once

#include <LogSeverity.h>
#include <string>
#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
    namespace IO
    {
        struct InputContextMapperDescriptor
        {
            Core::LogSeverity log_level;
			
			std::string action_slots_config_file;
			std::string input_layout_config_file;
			
			Core::IComponent* update_frame_provider;
			
            InputContextMapperDescriptor():
            log_level(Core::LogSeverity::NONE),
            update_frame_provider(nullptr)
            {}
        };
    }
}