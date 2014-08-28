#include <Components/TBBBaseOgreComponent.h>
#include <TBBOgreRenderSubsystem.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBBaseOgreComponent::TBBBaseOgreComponent ( const std::string& name, UnknownEngine::Graphics::OgreRenderSubsystem* render_subsystem, UnknownEngine::Core::EngineContext* engine_context ) :
			ThreadIndependentOgreComponentBase ( name, render_subsystem, engine_context )
		{
			render_subsystem->addSynchronizeCallback ( this->getName(), [this]()
				{
					if(listener) listener->flushAllMessageBuffers();
				} );
		}
		
		
		TBBBaseOgreComponent::~TBBBaseOgreComponent() 
		{
			
		}
		
		void TBBBaseOgreComponent::init ( const UnknownEngine::Core::Entity* parent_entity )
		{
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				initMessageListenerBuffers(true);
				render_subsystem->addInitCallback ( [this, parent_entity]()
				{
					this->internalInit ( parent_entity );
				} );
			}
			else
			{
				initMessageListenerBuffers(false);
				this->internalInit ( parent_entity );
			}
		}
		
		void TBBBaseOgreComponent::shutdown()
		{
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				render_subsystem->addShutdownCallback ( [this]()
				{
					this->internalShutdown ( );
				} );
			}
			else
			{
				this->internalShutdown();
			}
		}
	}
}
