#pragma once


#include <Components/BaseOgreComponent_fwd.h>
#include <Components/ThreadIndependentOgreComponentBase.h>
#include <MessageSystem/MessagingPoliciesManager.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine
{
	namespace Core
	{

		class EngineContext;
		class LogHelper;
	}

	namespace Graphics
	{

		class TBBBaseOgreComponent : public ThreadIndependentOgreComponentBase
		{
			public:
				TBBBaseOgreComponent ( const std::string &name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
					ThreadIndependentOgreComponentBase ( name, render_subsystem, engine_context)
				{}

				virtual ~TBBBaseOgreComponent() {};

				virtual void init ( const Core::Entity* parent_entity ) override
				{
					if ( render_subsystem->hasSeparateRenderThreadEnabled() )
					{
						render_subsystem->addInitCallback ( [this, parent_entity]()
						{
							this->internalInit ( parent_entity );
						} );
					}
					else
					{
						this->internalInit(parent_entity);
					}
				}

				virtual void shutdown ( ) override
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

		};

	}
}
