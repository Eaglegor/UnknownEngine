#include <stdafx.h>

#include <Factories/OgreCameraComponentsFactory.h>
#include <Components/OgreCameraComponent.h>
#include <Parsers/OgreCameraDescriptorParser.h>

#include <OgreRenderSubsystem.h>
#include <ComponentDesc.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreCameraComponentsFactory::OgreCameraComponentsFactory(OgreRenderSubsystem* render_system, Core::EngineContext *engine_context)
			:render_system(render_system),
			  engine_context(engine_context)
		{
			supported_types.insert(OGRE_CAMERA_COMPONENT_TYPE);
		}

		const std::string OgreCameraComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.CameraComponentsFactory";
		}

		const std::unordered_set<Core::ComponentType> &OgreCameraComponentsFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreCameraComponentsFactory::supportsType(const Core::ComponentType &object_type)
		{
			return supported_types.find(object_type)!=supported_types.end();
		}

		Core::Component *OgreCameraComponentsFactory::createObject(const Core::ComponentDesc &desc)
		{
			Core::Component* component = nullptr;

			if(desc.type == OGRE_CAMERA_COMPONENT_TYPE)
			{
				component = createCameraComponent(desc);
			}

			return component;
		}

		void OgreCameraComponentsFactory::destroyObject(Core::Component *object)
		{
			if(object->getType() == OGRE_CAMERA_COMPONENT_TYPE) destroyCameraComponent(object);
		}

		Core::Component *OgreCameraComponentsFactory::createCameraComponent(const Core::ComponentDesc &desc)
		{
			OgreCameraComponent* component;
			if(!desc.descriptor.isEmpty())
			{
				component = new OgreCameraComponent(desc.name, desc.descriptor.get<OgreCameraComponent::Descriptor>(), render_system, engine_context);
			}
			else
			{
				component = new OgreCameraComponent(desc.name, OgreCameraDescriptorParser::parse(desc.creation_options), render_system, engine_context);
			}
			registerCameraComponentListeners(component, desc.received_messages);
			return component;
		}

		void OgreCameraComponentsFactory::destroyCameraComponent(const Core::Component *component)
		{
			delete component;
		}

		void OgreCameraComponentsFactory::registerCameraComponentListeners(OgreCameraComponent* component, const Core::ReceivedMessageDescriptorsList &received_messages)
		{
			for(const Core::ReceivedMessageDesc &message_desc : received_messages)
			{
				component->addReceivedMessageType(message_desc);
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
