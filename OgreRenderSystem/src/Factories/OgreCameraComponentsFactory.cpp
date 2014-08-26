#include <stdafx.h>

#include <Factories/OgreCameraComponentsFactory.h>
#include <Components/Cameras/OgreCameraComponent.h>
#include <Parsers/Descriptors/OgreCameraDescriptorParser.h>

#include <OgreRenderSubsystem.h>
#include <ComponentDesc.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreCameraComponentsFactory::OgreCameraComponentsFactory ( OgreRenderSubsystem* render_subsystem, Core::EngineContext* engine_context, Core::LogHelper* log_helper ):
		BaseOgreComponentFactory(render_subsystem, engine_context, log_helper)
		{
			supported_types.insert ( OGRE_CAMERA_COMPONENT_TYPE );
		}

		const std::string OgreCameraComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.CameraComponentsFactory";
		}

		const std::unordered_set<Core::ComponentType> &OgreCameraComponentsFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreCameraComponentsFactory::supportsType ( const Core::ComponentType &object_type )
		{
			return supported_types.find ( object_type ) != supported_types.end();
		}

		Core::IComponent *OgreCameraComponentsFactory::internalCreateObject ( const Core::ComponentDesc &desc )
		{
			Core::IComponent* component = nullptr;

			if ( desc.type == OGRE_CAMERA_COMPONENT_TYPE )
			{
				component = createCameraComponent ( desc );
			}

			return component;
		}

		void OgreCameraComponentsFactory::internalDestroyObject ( Core::IComponent *object )
		{
			if ( object->getType() == OGRE_CAMERA_COMPONENT_TYPE ) destroyCameraComponent ( object );
		}

		Core::IComponent *OgreCameraComponentsFactory::createCameraComponent ( const Core::ComponentDesc &desc )
		{
			OgreCameraComponent* component;
			if ( !desc.descriptor.isEmpty() )
			{
				component = new OgreCameraComponent ( desc.name, desc.descriptor.get<OgreCameraComponentDescriptor>(), render_subsystem, engine_context );
			}
			else
			{
				component = new OgreCameraComponent ( desc.name, OgreCameraDescriptorParser::parse ( desc.creation_options ), render_subsystem, engine_context );
			}
			registerCameraComponentListeners ( component, desc.received_messages );
			return component;
		}

		void OgreCameraComponentsFactory::destroyCameraComponent ( const Core::IComponent *component )
		{
			delete component;
		}

		void OgreCameraComponentsFactory::registerCameraComponentListeners ( OgreCameraComponent* component, const Core::ReceivedMessageDescriptorsList &received_messages )
		{
			for ( const Core::ReceivedMessageDesc & message_desc : received_messages )
			{
				component->addReceivedMessageType ( message_desc );
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
