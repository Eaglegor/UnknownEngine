#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentSystem/IEntity.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <ComponentInterfaces/Engine/IStartableComponent.h>
#include <ComponentInterfaces/Input/IContextualActionsMapper.h>
#include <Descriptors/SimpleEngineStopperDesc.h>

class SimpleEngineStopperDesc;
namespace UnknownEngine
{
    namespace Behavior
    {
        class SimpleEngineStopperComponent :
        public Core::BaseComponent
        {
        public:
            SimpleEngineStopperComponent(const char* name, const SimpleEngineStopperDesc &desc);

            virtual void init(Core::IEntity const *parent_entity);

            virtual void shutdown();

            constexpr static const char* getTypeName(){return "Behavior.SimpleEngineStopper";}
            virtual Core::ComponentType getType() const{return getTypeName();}

        private:
            Core::ComponentInterfacePtr<ComponentInterfaces::IContextualActionsMapper> input_context_mapping_provider;
            Core::ComponentInterfacePtr<ComponentInterfaces::IStartableComponent> engine_starter;
            SimpleEngineStopperDesc desc;
        };
    }
}