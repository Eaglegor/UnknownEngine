#pragma once
#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <IComponentFactory.h>
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

		class SingleThreadedBaseOgreComponentFactory : public Core::IComponentFactory
		{
			public:
				virtual void destroyObject ( Core::Component* object )
				{
					internalDestroyObject(object);
				}

				virtual ~SingleThreadedBaseOgreComponentFactory(){};
				SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
					render_subsystem ( render_subsystem ),
					engine_context ( engine_context ),
					log_helper ( log_helper ) {}

					
			protected:
				virtual void internalDestroyObject ( Core::Component* object ) = 0;

				std::unordered_set<Core::ComponentType> supported_types;
				Core::LogHelper* log_helper;
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
		};
	}
}
