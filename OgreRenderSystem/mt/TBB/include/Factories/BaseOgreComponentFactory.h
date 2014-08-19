#pragma once

#include <Factories/BaseOgreComponentFactory_fwd.h>
#include <IComponentFactory.h>
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

		class TBBBaseOgreComponentFactory : public Core::IComponentFactory
		{
			public:
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

				virtual ~TBBBaseOgreComponentFactory(){};
				TBBBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
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
