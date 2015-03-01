#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	
    namespace Behavior
    {
        struct SimpleStopperDesc
        {
            std::string input_context_name;
			std::string action_name;
            Core::IComponent* stoppable_component;
            Core::IComponent* input_context_mapping_provider;

            SimpleStopperDesc():
            stoppable_component(nullptr),
            input_context_mapping_provider(nullptr)
            {}
        };
    }
}