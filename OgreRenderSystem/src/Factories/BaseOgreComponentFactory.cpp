#include <Factories/BaseOgreComponentFactory.h>
#include <OgreRenderSubsystem.h>
#include <Objects/Component.h>

namespace UnknownEngine {
	namespace Graphics
	{

		BaseOgreComponentFactory::~BaseOgreComponentFactory()
		{
		}
		
		BaseOgreComponentFactory::BaseOgreComponentFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ):
		render_subsystem(render_subsystem),
		engine_context(engine_context),
		log_helper(log_helper)
		{
		}
		
		void BaseOgreComponentFactory::destroyObject ( Core::Component* object )
		{
#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			if(render_subsystem->hasSeparateRenderThreadEnabled())
			{
				render_subsystem->addRemoveCallback(object->getName(), [this, object](){internalDestroyObject(object);});
			}
			else
#endif
				internalDestroyObject(object);
		}
	}
}