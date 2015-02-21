#include <stdafx.h>

#include <Components/BaseOgreComponent.h>
#include <OgreRenderSubsystem.h>
#include <Logging.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine {
	namespace Graphics
	{
		BaseOgreComponent::BaseOgreComponent ( const std::string& name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
			Core::BaseComponent(name.c_str()),
			shutdown_initialized(false),
			render_subsystem ( render_subsystem )
		{
		}
		
		BaseOgreComponent::~BaseOgreComponent() {
		}
		
		void BaseOgreComponent::init ( const UnknownEngine::Core::IEntity* parent_entity )
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
			
			render_subsystem->addSynchronizeCallback ( this->getName(), [this]()
				{
					if(!shutdown_initialized) 
					{
						if(listener)
						{
							listener->flushAllMessageBuffers();
						}
						this->update();
					}
				} );
		}
		
		void BaseOgreComponent::shutdown()
		{
			render_subsystem->removeSynchronizeCallback ( this->getName() );
			
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				shutdown_initialized = true;
				render_subsystem->addShutdownCallback ( [this]()
				{
					this->internalShutdown ( );
					shutdown_initialized = false;
				} );
			}
			else
			{
				this->internalShutdown();
			}
		}
		
		void BaseOgreComponent::setMessageListener ( std::unique_ptr< Core::BaseMessageListener > listener )
		{
			this->listener = std::move(listener);
		}

	}
}