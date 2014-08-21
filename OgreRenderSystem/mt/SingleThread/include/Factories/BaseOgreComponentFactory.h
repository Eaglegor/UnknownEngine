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
				virtual ~SingleThreadedBaseOgreComponentFactory(){};
				SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
					ThreadIndependentOgreComponentFactoryBase(render_subsystem, engine_context, log_helper){}

				virtual Core::Component* createObject ( const Core::ComponentDesc& desc )
				{
					return internalCreateObject(desc);
				}

				virtual void destroyObject ( Core::Component* object )
				{
					internalDestroyObject(object);
				}

		};
	}
}
