#pragma once

#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <Factories/ThreadIndependentOgreComponentFactoryBase.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class TBBBaseOgreComponentFactory : public ThreadIndependentOgreComponentFactoryBase
		{
			public:

				TBBBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper );
				virtual ~TBBBaseOgreComponentFactory();

				virtual Core::IComponent* createObject (const Core::ComponentDesc &desc);

				virtual void destroyObject ( Core::IComponent* object );

		};
	}
}
