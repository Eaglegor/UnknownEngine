#include <Components/SimpleEngineStopperComponent.h>
#include <ComponentSystem/IEntity.h>
#include <Descriptors/SimpleEngineStopperDesc.h>

namespace UnknownEngine
{
    namespace Behavior
    {

        SimpleEngineStopperComponent::SimpleEngineStopperComponent(const char *name, const SimpleEngineStopperDesc &desc):
        Core::BaseComponent(name),
        input_context_mapping_provider(desc.input_context_mapping_provider),
        engine_starter(desc.engine_starter_component)
        {
        }

        void SimpleEngineStopperComponent::init(Core::IEntity const *parent_entity) {
            if(input_context_mapping_provider)
            {
                input_context_mapping_provider->addSimpleAction(desc.input_context_name.c_str(), "StopEngine", [this](){this->engine_starter->stop();});
            }
        }

        void SimpleEngineStopperComponent::shutdown() {
            if(input_context_mapping_provider)
            {
                input_context_mapping_provider->removeSimpleAction(desc.input_context_name.c_str(), "StopEngine");
            }
        }

    }
}