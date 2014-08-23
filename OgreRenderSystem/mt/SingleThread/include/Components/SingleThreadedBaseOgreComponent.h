#pragma once

#include <Components/ThreadIndependentOgreComponentBase.h>
#include <Components/BaseOgreComponent_fwd.h>
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

		class SingleThreadedBaseOgreComponent : public ThreadIndependentOgreComponentBase
		{
		public:
			SingleThreadedBaseOgreComponent(const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context);
			virtual ~SingleThreadedBaseOgreComponent();
			
			virtual void init ( const Core::Entity* parent_entity ) override;
			virtual void shutdown ( ) override;

		};
		
	}
}