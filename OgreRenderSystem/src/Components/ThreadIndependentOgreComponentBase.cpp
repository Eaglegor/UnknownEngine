#include <stdafx.h>

#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>

namespace UnknownEngine {
	namespace Graphics
	{
		ThreadIndependentOgreComponentBase::ThreadIndependentOgreComponentBase ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
			Core::Component ( name ),
			render_subsystem ( render_subsystem ),
			engine_context ( engine_context ),
			messaging_policies_manager ( engine_context )
		{}
		
		ThreadIndependentOgreComponentBase::~ThreadIndependentOgreComponentBase() {
			
		}
	}
}