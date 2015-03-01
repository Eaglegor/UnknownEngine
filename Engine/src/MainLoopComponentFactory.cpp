#include <MainLoopComponentFactory.h>
#include <MainLoop/MainLoopComponent.h>
#include <ComponentSystem/ComponentDesc.h>
#include <EngineStarterComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
        EngineCoreComponentsFactory::EngineCoreComponentsFactory(Engine &engine):
        engine(engine)
		{
			CreatableObjectDesc desc;
			desc.type = MainLoopComponent::getTypeName();
			desc.creator = std::bind(&EngineCoreComponentsFactory::createMainLoopComponent, this, std::placeholders::_1);
			registerCreator(desc);

            desc.type = EngineStarterComponent::getTypeName();
            desc.creator = std::bind(&EngineCoreComponentsFactory::createEngineStarterComponent, this, std::placeholders::_1);
            registerCreator(desc);
		}
		
		const char* EngineCoreComponentsFactory::getName() const
		{
			return "Engine.EngineCoreComponentFactory";
		}

		IComponent* EngineCoreComponentsFactory::createMainLoopComponent(const ComponentDesc& desc)
		{
			return new MainLoopComponent(desc.name.c_str());
		}

        IComponent* EngineCoreComponentsFactory::createEngineStarterComponent(const ComponentDesc& desc)
        {
            return new EngineStarterComponent(desc.name.c_str(), engine);
        }
	}
}