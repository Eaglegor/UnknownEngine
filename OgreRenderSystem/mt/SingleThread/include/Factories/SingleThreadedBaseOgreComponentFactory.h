#pragma once
#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <Factories/ThreadIndependentOgreComponentFactoryBase.h>
#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
	}

	namespace Utils
	{
		class LogHelper;
	}
	
	namespace Graphics
	{

		class SingleThreadedBaseOgreComponentFactory : public ThreadIndependentOgreComponentFactoryBase
		{
			public:
				SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper );
				virtual ~SingleThreadedBaseOgreComponentFactory();

				virtual Core::IComponent* createObject ( const Core::ComponentDesc& desc );

				virtual void destroyObject ( Core::IComponent* object );

		};
	}
}
