#include <stdafx.h>

#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine {
	namespace Graphics
	{
		ThreadIndependentOgreComponentBase::ThreadIndependentOgreComponentBase ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
			Core::BaseComponent(name),
			render_subsystem ( render_subsystem )
		{}
		
		ThreadIndependentOgreComponentBase::~ThreadIndependentOgreComponentBase() {
			
		}
		
		void ThreadIndependentOgreComponentBase::setMessageListener ( std::unique_ptr< Core::BaseMessageListener > listener )
		{
			this->listener = std::move(listener);
		}

	}
}