#include <MainLoopComponentFactory.h>
#include <MainLoop/MainLoopComponent.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace Core
	{
		MainLoopComponentFactory::MainLoopComponentFactory()
		{
			CreatableObjectDesc desc;
			desc.type = MainLoopComponent::getTypeName();
			desc.creator = std::bind(&MainLoopComponentFactory::createMainLoopComponent, this, std::placeholders::_1);
			registerCreator(desc);
		}
		
		const char* MainLoopComponentFactory::getName() const
		{
			return "Engine.MainLoopComponentFactory";
		}

		IComponent* MainLoopComponentFactory::createMainLoopComponent(const ComponentDesc& desc)
		{
			return new MainLoopComponent(desc.name.c_str());
		}
	}
}