#include <Factories/TBBBaseOgreComponentFactory.h>
#include <TBBOgreRenderSubsystem.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBBaseOgreComponentFactory::TBBBaseOgreComponentFactory ( UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Core::LogHelper* log_helper ) :
			ThreadIndependentOgreComponentFactoryBase ( render_subsystem, engine_context, log_helper ) 
			{
				
			}
			
		TBBBaseOgreComponentFactory::~TBBBaseOgreComponentFactory() 
		{
			
		}
		
		UnknownEngine::Core::Component* TBBBaseOgreComponentFactory::createObject ( const UnknownEngine::Core::ComponentDesc& desc )
		{
			return internalCreateObject ( desc );
		}
		
		void TBBBaseOgreComponentFactory::destroyObject ( UnknownEngine::Core::Component* object )
		{
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				render_subsystem->addRemoveCallback ( [this, object]()
				{
					internalDestroyObject ( object );
				} );
			}
			else
			{
				internalDestroyObject ( object );
			}
		}
	}
}
