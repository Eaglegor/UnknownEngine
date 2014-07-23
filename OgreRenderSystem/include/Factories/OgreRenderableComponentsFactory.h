#pragma once

#include <IComponentFactory.h>
#include <ComponentDesc.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Exception.h>

namespace UnknownEngine {

	namespace Core
	{
		class EngineContext;
		class IMessageListener;
	}

	namespace Graphics {

		class OgreRenderSubsystem;
		class OgreRenderableComponent;

		/**
		 * @brief Factory for creating solid and compound non-deformable (mesh doesn't change during the whole lifetime) renderable components
		 */
		class OgreRenderableComponentsFactory: public Core::IComponentFactory
		{
			public:

				UNKNOWNENGINE_SIMPLE_EXCEPTION(ListenerIsNotAbleToProcessMessageType);

				OgreRenderableComponentsFactory(OgreRenderSubsystem* render_system, Core::EngineContext *engine_context);

				/**
				 * @brief Returns a factory name.
				 *
				 * The name must be unique across all registered factories.
				 *
				 * @return Factory name
				 */
				virtual const std::string getName();

				/**
				 * @brief Returns a set of object type identifiers supported by this factory
				 * @return Set of identifiers of object types which can be created by this factory
				 */
				virtual const std::unordered_set<Core::ComponentType>& getSupportedTypes();

				/**
				 * @brief Checks if a factory is able to create specific type
				 * @param object_type - Type to check for
				 * @return true if the factory supports passed type
				 */
				virtual const bool supportsType(const Core::ComponentType &object_type);

				/**
				 * @brief Creates an object according to passed descriptor
				 * @param desc - Object descriptor
				 * @return Pointer to a newly created object
				 */
				virtual Core::Component* createObject(const Core::ComponentDesc& desc);

				/**
				 * @brief Deletes object considering it's creation process
				 * @param object - The object to be deleted
				 */
				virtual void destroyObject(Core::Component* object);

			private:

				// Solid renderable components
				Core::Component* createRenderableComponent(const Core::ComponentDesc &desc);
				void destroyRenderableComponent(const Core::Component* component);
				void registerRenderableComponentListeners(OgreRenderableComponent* component, const Core::ComponentDesc::ListenerDescriptorsList &listeners);
				void registerRenderableComponentListener(Core::IMessageListener* listener, const Core::MessageListenerDesc::MessageDesc &message_desc);

				Core::EngineContext* engine_context;
				std::unordered_set<Core::ComponentType> supported_types;
				OgreRenderSubsystem* render_system;
		};

	} // namespace Graphics
} // namespace UnknownEngine
