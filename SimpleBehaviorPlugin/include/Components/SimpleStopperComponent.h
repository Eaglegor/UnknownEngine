#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentSystem/IEntity.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Engine/IStartableComponent.h>
#include <ComponentInterfaces/Input/IContextualActionsMapper.h>
#include <Descriptors/SimpleStopperDesc.h>

namespace UnknownEngine
{
    namespace Behavior
    {
        class SimpleStopperComponent :
        public Core::BaseComponent
        {
        public:
            SimpleStopperComponent(const char* name, const SimpleStopperDesc &desc);

            virtual void init(Core::IEntity const *parent_entity);

            virtual void shutdown();

            constexpr static const char* getTypeName(){return "Behavior.SimpleStopper";}
            virtual Core::ComponentType getType() const{return getTypeName();}

        private:
            Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapping_provider;
            Core::ComponentInterfacePtr<ComponentInterfaces::IStartableComponent> stoppable;
            SimpleStopperDesc desc;
        };
    }
}