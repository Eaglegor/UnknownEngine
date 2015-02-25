#include <EngineStarterComponent.h>
#include <Engine.h>

namespace UnknownEngine
{
    namespace Core
    {

        EngineStarterComponent::EngineStarterComponent(const char *name, Engine &engine):
        Core::BaseComponent(name),
        engine(engine)
        {
        }

        void EngineStarterComponent::start() {
            engine.start();
        }

        void EngineStarterComponent::stop() {
            engine.stop();
        }

        void EngineStarterComponent::init() {
        }

        void EngineStarterComponent::shutdown() {
        }

        IComponentInterface *EngineStarterComponent::getInterface(const ComponentType &type) {
            if(type == ComponentInterfaces::IStartableComponent::getTypeName()) return static_cast<ComponentInterfaces::IStartableComponent*>(this);
            return nullptr;
        }
    }
}