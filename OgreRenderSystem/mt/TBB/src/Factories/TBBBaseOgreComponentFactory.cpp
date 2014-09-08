#include <Factories/TBBBaseOgreComponentFactory.h>
#include <TBBOgreRenderSubsystem.h>
#include <Components/TBBBaseOgreComponent.h>

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

		UnknownEngine::Core::IComponent* TBBBaseOgreComponentFactory::createObject ( const UnknownEngine::Core::ComponentDesc& desc )
		{
			return Core::BaseComponentFactory::createObject ( desc );
		}

		void TBBBaseOgreComponentFactory::destroyObject ( UnknownEngine::Core::IComponent* object )
		{
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				render_subsystem->addRemoveCallback (
				    [this, object]()
					{
						Core::BaseComponentFactory::destroyObject ( object );
					}
				);
			}
			else
			{
				Core::BaseComponentFactory::destroyObject ( object );
			}
		}
	}
}
