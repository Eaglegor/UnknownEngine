#include <stdafx.h>

#include <Factories/OgreRenderableComponentsFactory.h>
#include <Components/OgreRenderableComponent.h>
#include <Parsers/OgreRenderableDescriptorParser.h>
#include <OgreRenderSubsystem.h>
#include <ComponentDesc.h>
#include <ExportedMessages/TransformChangedMessage.h>
#include <ExportedMessages/RenderSystem/ChangeMaterialActionMessage.h>
#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderableComponentsFactory::OgreRenderableComponentsFactory(OgreRenderSubsystem* render_system, Core::EngineContext *engine_context)
			:render_system(render_system),
			  engine_context(engine_context)
		{
			supported_types.insert(OGRE_RENDERABLE_COMPONENT_TYPE);
		}

		const std::string OgreRenderableComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSystem.RenderableComponentsFactory";
		}

		const std::unordered_set<Core::ComponentType> &OgreRenderableComponentsFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreRenderableComponentsFactory::supportsType(const Core::ComponentType &object_type)
		{
			return supported_types.find(object_type)!=supported_types.end();
		}

		Core::Component *OgreRenderableComponentsFactory::createObject(const Core::ComponentDesc &desc)
		{
			Core::Component* component = nullptr;

			if(desc.type == OGRE_RENDERABLE_COMPONENT_TYPE)
			{
				component = createRenderableComponent(desc);
			}

			return component;
		}

		void OgreRenderableComponentsFactory::destroyObject(Core::Component *object)
		{
			if(object->getType() == OGRE_RENDERABLE_COMPONENT_TYPE) destroyRenderableComponent(object);
		}

		Core::Component *OgreRenderableComponentsFactory::createRenderableComponent(const Core::ComponentDesc &desc)
		{
			OgreRenderableComponent* component;
			if(!desc.descriptor.isEmpty())
			{
				component = new OgreRenderableComponent(desc.name, desc.descriptor.get<OgreRenderableComponent::Descriptor>(), render_system, engine_context);
			}
			else
			{
				component = new OgreRenderableComponent(desc.name, OgreRenderableDescriptorParser::parse(desc.creation_options), render_system, engine_context);
			}
			registerRenderableComponentListeners(component, desc.message_listeners_desc);
			return component;
		}

		void OgreRenderableComponentsFactory::destroyRenderableComponent(const Core::Component *component)
		{
			delete component;
		}

		void OgreRenderableComponentsFactory::registerRenderableComponentListeners(OgreRenderableComponent* component, const Core::ComponentDesc::ListenerDescriptorsList &listener_descriptors)
		{
			for(const Core::MessageListenerDesc &listener_desc : listener_descriptors)
			{
				Core::IMessageListener *listener = component->createListener(listener_desc.name, engine_context);
				for(const Core::MessageListenerDesc::MessageDesc &message_desc : listener_desc.messages)
				{
					registerRenderableComponentListener(listener, message_desc);
				}
			}
		}

		void OgreRenderableComponentsFactory::registerRenderableComponentListener(Core::IMessageListener *listener, const Core::MessageListenerDesc::MessageDesc &message_desc)
		{
			if(message_desc.message_type_name == Core::TransformChangedMessage::getTypeName() ||
					message_desc.message_type_name == Graphics::ChangeMaterialActionMessage::getTypeName())
			{
				engine_context->getMessageDispatcher()->addListener(message_desc.message_type_name, listener);
			}
			else
			{
				throw ListenerIsNotAbleToProcessMessageType("Listener " + listener->getName() + " is not able to process the message type " + message_desc.message_type_name);
			}
		}

	} // namespace Graphics
} // namespace UnknownEngine
