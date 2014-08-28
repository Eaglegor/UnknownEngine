#include <stdafx.h>

#include <Factories/OgreRenderableComponentsFactory.h>
#include <Components/Renderables/OgreRenderableComponent.h>
#include <Parsers/Descriptors/OgreRenderableDescriptorParser.h>
#include <OgreRenderSubsystem.h>
#include <ComponentDesc.h>

#include <EngineContext.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/BaseMessageListener.h>

#include <LogHelper.h>
#include <Listeners/BaseMessageListenersFactory.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderableComponentsFactory::OgreRenderableComponentsFactory ( UnknownEngine::Graphics::OgreRenderSubsystem* render_system, UnknownEngine::Core::EngineContext* engine_context, UnknownEngine::Core::LogHelper* log_helper )
			: BaseOgreComponentFactory(render_system, engine_context, log_helper)
		{
			supported_types.insert ( OGRE_RENDERABLE_COMPONENT_TYPE );
		}

		const char* OgreRenderableComponentsFactory::getName()
		{
			return "Graphics.OgreRenderSubsystem.RenderableComponentsFactory";
		}

		const std::unordered_set<Core::ComponentType> &OgreRenderableComponentsFactory::getSupportedTypes()
		{
			return supported_types;
		}

		const bool OgreRenderableComponentsFactory::supportsType ( const Core::ComponentType &object_type )
		{
			return supported_types.find ( object_type ) != supported_types.end();
		}

		Core::IComponent *OgreRenderableComponentsFactory::internalCreateObject ( const Core::ComponentDesc &desc )
		{
			Core::IComponent* component = nullptr;

			if ( desc.type == OGRE_RENDERABLE_COMPONENT_TYPE )
			{
				component = createRenderableComponent ( desc );
			}

			return component;
		}

		void OgreRenderableComponentsFactory::internalDestroyObject ( Core::IComponent *object )
		{
			if ( object->getType() == OGRE_RENDERABLE_COMPONENT_TYPE ) destroyRenderableComponent ( object );
		}

		Core::IComponent *OgreRenderableComponentsFactory::createRenderableComponent ( const Core::ComponentDesc &desc )
		{
			LOG_INFO ( log_helper, "Creating renderablec component" );
			OgreRenderableComponent* component;
			if ( !desc.descriptor.isEmpty() )
			{
				LOG_INFO ( log_helper, "Predefined descriptor found" );
				component = new OgreRenderableComponent ( desc.name, desc.descriptor.get<OgreRenderableComponentDescriptor>(), render_subsystem, engine_context );
			}
			else
			{
				LOG_WARNING ( log_helper, "Predefined descriptor not found. String parser will be used instead." );
				component = new OgreRenderableComponent ( desc.name, OgreRenderableDescriptorParser::parse ( desc.creation_options ), render_subsystem, engine_context );
			}
			LOG_INFO ( log_helper, "Registering component's listeners" );
			registerRenderableComponentListeners ( component, desc.received_messages );

			LOG_INFO ( log_helper, "Component created" );
			return component;
		}

		void OgreRenderableComponentsFactory::destroyRenderableComponent ( const Core::IComponent *component )
		{
			delete component;
		}

		void OgreRenderableComponentsFactory::registerRenderableComponentListeners ( OgreRenderableComponent* component, const Core::ReceivedMessageDescriptorsList &received_messages )
		{
			std::unique_ptr<Core::BaseMessageListener> listener = Utils::BaseMessageListenersFactory::createBaseMessageListener(
				std::string(component->getName())+".Listener",
				engine_context,
				received_messages
			);
			
			component->setMessageListener(std::move(listener));			
		}

		OgreRenderableComponentsFactory::~OgreRenderableComponentsFactory()
		{
		}

	} // namespace Graphics
} // namespace UnknownEngine
