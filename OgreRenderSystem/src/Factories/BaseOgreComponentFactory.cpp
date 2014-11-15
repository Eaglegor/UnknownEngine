#include <stdafx.h>
#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSystem.h>
#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		BaseOgreComponentFactory::BaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Utils::LogHelper* log_helper ):
		render_subsystem(render_subsystem),
		engine_context(engine_context),
		log_helper(log_helper)
		{

		}

		BaseOgreComponentFactory::~BaseOgreComponentFactory()
		{
		}

		void BaseOgreComponentFactory::destroyObject ( UnknownEngine::Core::IComponent* object )
		{
			render_subsystem->addRemoveCallback (
				[this, object]()
				{
					Core::BaseComponentFactory::destroyObject ( object );
				}
			);
		}
	}
}
