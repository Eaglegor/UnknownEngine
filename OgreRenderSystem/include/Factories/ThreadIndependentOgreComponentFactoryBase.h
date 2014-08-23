#pragma once
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

		class ThreadIndependentOgreComponentFactoryBase : public Core::IComponentFactory
		{
			public:

				virtual ~ThreadIndependentOgreComponentFactoryBase(){};
				ThreadIndependentOgreComponentFactoryBase ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
					render_subsystem ( render_subsystem ),
					engine_context ( engine_context ),
					log_helper ( log_helper ) {}

			protected:
				virtual Core::Component* internalCreateObject ( const Core::ComponentDesc& desc ) = 0;
				virtual void internalDestroyObject ( Core::Component* object ) = 0;

				std::unordered_set<Core::ComponentType> supported_types;
				Core::LogHelper* log_helper;
				OgreRenderSubsystem* render_subsystem;
				Core::EngineContext* engine_context;
		};
	}
}
