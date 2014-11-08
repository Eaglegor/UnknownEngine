#include <stdafx.h>
#include <Factories/SingleThreadedBaseOgreComponentFactory.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		SingleThreadedBaseOgreComponentFactory::SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper ) :
			ThreadIndependentOgreComponentFactoryBase ( render_subsystem, engine_context, log_helper ) {}
		
		SingleThreadedBaseOgreComponentFactory::~SingleThreadedBaseOgreComponentFactory() {}
		
		Core::IComponent* SingleThreadedBaseOgreComponentFactory::createObject ( const Core::ComponentDesc& desc )
		{
			return Core::BaseComponentFactory::createObject ( desc );
		}
		
		void SingleThreadedBaseOgreComponentFactory::destroyObject ( Core::IComponent* object )
		{
			Core::BaseComponentFactory::destroyObject ( object );
		}
		
	}
}