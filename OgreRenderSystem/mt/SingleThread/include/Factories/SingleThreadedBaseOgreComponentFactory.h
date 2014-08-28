#pragma once
#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <Factories/ThreadIndependentOgreComponentFactoryBase.h>
#include <OgreRenderSubsystem_fwd.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class SingleThreadedBaseOgreComponentFactory : public ThreadIndependentOgreComponentFactoryBase
		{
			public:
				SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper );
				virtual ~SingleThreadedBaseOgreComponentFactory();

				virtual Core::IComponent* createObject ( const Core::ComponentDesc& desc );

				virtual void destroyObject ( Core::IComponent* object );

		};
	}
}
