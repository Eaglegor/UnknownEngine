#include <Components/SimpleStopperComponent.h>
#include <ComponentSystem/IEntity.h>

namespace UnknownEngine
{
    namespace Behavior
    {

        SimpleStopperComponent::SimpleStopperComponent(const char *name, const SimpleStopperDesc &desc):
        Core::BaseComponent(name),
        input_context_mapping_provider(desc.input_context_mapping_provider),
        stoppable(desc.stoppable_component),
        desc(desc)
        {
        }

        void SimpleStopperComponent::init() {
            if(input_context_mapping_provider)
            {
                input_context_mapping_provider->addSimpleAction(desc.input_context_name.c_str(), desc.action_name.c_str(), [this](){if(this->stoppable) this->stoppable->stop();});
            }
        }

        void SimpleStopperComponent::shutdown() {
            if(input_context_mapping_provider)
            {
                input_context_mapping_provider->removeSimpleAction(desc.input_context_name.c_str(), desc.action_name.c_str());
            }
        }

    }
}