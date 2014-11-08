#include <stdafx.h>
#include <Factories/TBBBaseOgreComponentFactory.h>
#include <TBBOgreRenderSubsystem.h>
#include <Components/TBBBaseOgreComponent.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBBaseOgreComponentFactory::TBBBaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper ) :
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
