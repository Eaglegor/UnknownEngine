#include <Listeners/TBBBaseOgreComponentListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		TBBOgreComponentListener::TBBOgreComponentListener ( const std::string& object_name, OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context ) :
			ThreadIndependentOgreComponentListenerBase ( object_name, render_subsystem, engine_context )
		{
			if ( render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				transform_changed_message_type = engine_context->getMessageDictionary()->getMessageTypeId(Core::TransformChangedMessage::getTypeName());
				render_subsystem->addSynchronizeCallback ( this->getName(), [this]()
				{
					this->processAllQueuedMessages();
				} );
			}
		}

		TBBOgreComponentListener::~TBBOgreComponentListener()
		{
			if ( this->render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				this->render_subsystem->removeSynchronizeCallback ( this->getName() );
			}
		}

		void TBBOgreComponentListener:: processMessage ( const Core::PackedMessage& msg )
		{
			if ( this->render_subsystem->hasSeparateRenderThreadEnabled() )
			{
				if(msg.getMessageTypeId() == transform_changed_message_type)
				{
					transform_changed_dedicated_queue.clear();
					transform_changed_dedicated_queue.push(msg);
				}
				else
				{
					messages_queue.push ( msg );
				}
			}
			else
			{
				this->internalProcessMessage ( msg );
			}
		}

		void TBBOgreComponentListener::processAllQueuedMessages()
		{
			Core::PackedMessage current_msg;
			while ( messages_queue.try_pop ( current_msg ) )
			{
				this->internalProcessMessage ( current_msg );
			}
			while ( transform_changed_dedicated_queue.try_pop ( current_msg ) )
			{
				this->internalProcessMessage ( current_msg );
			}
		}
	}
}
