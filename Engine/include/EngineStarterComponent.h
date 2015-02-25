#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <ComponentInterfaces/Engine/IStartableComponent.h>
#include <ComponentSystem/IEntity.h>

namespace UnknownEngine
{
    namespace Core
    {
        class Engine;

        class EngineStarterComponent :
                public Core::BaseComponent,
                public ComponentInterfaces::IStartableComponent
        {
        public:
            EngineStarterComponent(const char* name, Engine &engine);

            virtual void start() override;

            virtual void stop() override;

            virtual void init() override;

            virtual void shutdown() override;

            virtual IComponentInterface *getInterface(const ComponentType &type) override;

            constexpr static const char* getTypeName(){return "Engine.EngineStarterComponent";}
            virtual ComponentType getType() const override {return getTypeName();}

        private:
            Engine &engine;
        };
    }
}