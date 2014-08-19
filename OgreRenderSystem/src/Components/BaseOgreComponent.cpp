#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>

namespace UnknownEngine {
	namespace Graphics
	{
		
		BaseOgreComponent::BaseOgreComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
		Core::Component ( name ),
		render_subsystem(render_subsystem),
		engine_context(engine_context),
		messaging_policies_manager(engine_context)
		{
		}

		BaseOgreComponent::~BaseOgreComponent()
		{
		}
		
		void BaseOgreComponent::init ( const Core::Entity* parent_entity )
		{
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			if(!render_subsystem->hasSeparateRenderThreadEnabled())
			{
#endif
			internalInit(parent_entity);
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			}
			else
			{
				render_subsystem->addInitCallback(getName(), [this, parent_entity](){this->internalInit(parent_entity);});
			}
#endif

		}

		void BaseOgreComponent::shutdown()
		{
			internalShutdown();
		}
		
	}
}