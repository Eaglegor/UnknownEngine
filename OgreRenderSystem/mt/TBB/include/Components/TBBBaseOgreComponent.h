#pragma once

#include <Components/BaseOgreComponent_fwd.h>
#include <Components/ThreadIndependentOgreComponentBase.h>

namespace UnknownEngine
{
	namespace Core
	{
		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{
		class TBBBaseOgreComponent : public ThreadIndependentOgreComponentBase
		{
			public:
				TBBBaseOgreComponent ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context );

				virtual ~TBBBaseOgreComponent();

				virtual void init ( const Core::Entity* parent_entity ) override;

				virtual void shutdown ( ) override;
				
			private:
				bool shutdown_initialized;
			
		};

	}
}
