#include <Listeners/OgreCameraComponentListener.h>
#include <Components/OgreCameraComponent.h>

#define MessageProcessor(processor) &OgreCameraComponentListener::processor

namespace UnknownEngine
{
	namespace Graphics
	{

		std::unordered_set<std::string> OgreCameraComponentListener::supported_message_type_names;

		OgreCameraComponentListener::OgreCameraComponentListener ( const std::string& object_name, OgreCameraComponent* camera_component, Core::EngineContext* engine_context )
			: BaseOgreComponentListener< UnknownEngine::Graphics::OgreCameraComponentListener > ( object_name ),
			  camera_component ( camera_component ),
			  engine_context ( engine_context )
		{
			registerProcessor<Core::TransformChangedMessage> ( MessageProcessor ( processTransformChangedMessage ), engine_context );
		}

		void OgreCameraComponentListener::processTransformChangedMessage ( const PackedMessage& msg )
		{
			if ( camera_component != nullptr )
			{
				camera_component->onTransformChanged ( transform_message_unpacker.unpackMessage ( msg ) );
			}
		}

	}
}
