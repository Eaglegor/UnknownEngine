#include <Listeners/OgreCameraComponentListener.h>
#include <Components/OgreCameraComponent.h>
#include <MessageSystem/PackedMessage.h>

#define MessageProcessor(processor) &OgreCameraComponentListener::processor

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreCameraComponentListener::OgreCameraComponentListener ( const std::string &object_name, OgreCameraComponent *camera_component, Core::EngineContext *engine_context )
			: BaseOgreComponentListener< UnknownEngine::Graphics::OgreCameraComponentListener > ( object_name ),
			  camera_component ( camera_component ),
			  engine_context ( engine_context )
		{
			registerProcessor<Core::TransformChangedMessage> ( MessageProcessor ( processTransformChangedMessage ), engine_context );
		}

		void OgreCameraComponentListener::processTransformChangedMessage ( const Core::PackedMessage &msg )
		{
			if ( camera_component != nullptr )
			{
				camera_component->onTransformChanged ( transform_message_unpacker.unpackMessage ( msg ) );
			}
		}

		void OgreCameraComponentListener::processCameraLookAtActionMessage ( const Core::PackedMessage &msg )
		{
			if ( camera_component != nullptr )
			{
				camera_component->doLookAt ( camera_look_at_message_unpacker.unpackMessage ( msg ) );
			}
		}

	}
}
