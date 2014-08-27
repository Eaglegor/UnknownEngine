#include <Components/SingleThreadedBaseOgreComponent.h>

namespace UnknownEngine {
	namespace Graphics
	{
		
			SingleThreadedBaseOgreComponent::SingleThreadedBaseOgreComponent(const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context):
			ThreadIndependentOgreComponentBase ( name, render_subsystem, engine_context )
			{
				
			}
			
			SingleThreadedBaseOgreComponent::~SingleThreadedBaseOgreComponent()
			{
				
			}
		
			void SingleThreadedBaseOgreComponent::init ( const Core::Entity* parent_entity )
			{
				internalInit( parent_entity );
				registerListener();
			}
			
			void SingleThreadedBaseOgreComponent::shutdown ( )
			{
				unregisterListener();
				internalShutdown();
			}
	}
}