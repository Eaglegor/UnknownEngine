#include <Factories/SingleThreadedBaseOgreComponentFactory.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		SingleThreadedBaseOgreComponentFactory::SingleThreadedBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ) :
			ThreadIndependentOgreComponentFactoryBase ( render_subsystem, engine_context, log_helper ) {}
		
		SingleThreadedBaseOgreComponentFactory::~SingleThreadedBaseOgreComponentFactory() {}
		
		Core::Component* SingleThreadedBaseOgreComponentFactory::createObject ( const Core::ComponentDesc& desc )
		{
			return internalCreateObject ( desc );
		}
		
		void SingleThreadedBaseOgreComponentFactory::destroyObject ( Core::Component* object )
		{
			internalDestroyObject ( object );
		}
		
	}
}