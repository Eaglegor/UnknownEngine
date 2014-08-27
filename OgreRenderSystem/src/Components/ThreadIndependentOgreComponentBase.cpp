#include <stdafx.h>

#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>

namespace UnknownEngine {
	namespace Graphics
	{
		ThreadIndependentOgreComponentBase::ThreadIndependentOgreComponentBase ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
			Core::BaseComponent ( name, engine_context ),
			render_subsystem ( render_subsystem )
		{}
		
		ThreadIndependentOgreComponentBase::~ThreadIndependentOgreComponentBase() {
			
		}
	}
}