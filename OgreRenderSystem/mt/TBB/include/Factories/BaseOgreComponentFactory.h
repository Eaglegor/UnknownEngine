#pragma once

#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <Factories/ThreadIndependentOgreComponentFactoryBase.h>
#include <Objects/Component.h>
#include <OgreRenderSubsystem.h>

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

				TBBBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
					ThreadIndependentOgreComponentFactoryBase(render_subsystem, engine_context, log_helper){};
				virtual ~TBBBaseOgreComponentFactory(){};

				virtual Core::Component* createObject (const Core::ComponentDesc &desc)
				{
					return internalCreateObject(desc);
				}

				virtual void destroyObject ( Core::Component* object )
				{
					if(render_subsystem->hasSeparateRenderThreadEnabled())
					{
						render_subsystem->addRemoveCallback([this, object](){internalDestroyObject(object);});
					}
					else
					{
						internalDestroyObject(object);
					}
				}

		};
	}
}
