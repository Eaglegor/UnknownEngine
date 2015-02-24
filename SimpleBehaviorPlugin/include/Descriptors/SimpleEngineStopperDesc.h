#pragma once

namespace UnknownEngine
{
    namespace Behavior
    {
        struct SimpleEngineStopperDesc
        {
            std::string input_context_name;
            Core::IComponent* engine_starter_component;
            Core::IComponent* input_context_mapping_provider;

            SimpleEngineStopperDesc():
            engine_starter_component(nullptr),
            input_context_mapping_provider(nullptr)
            {}
        };
    }
}