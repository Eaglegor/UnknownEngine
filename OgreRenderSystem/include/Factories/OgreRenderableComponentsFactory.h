#ifndef UNKNOWNENGINE_GRAPHICS_RENDERABLECOMPONENTSFACTORY_H
#define UNKNOWNENGINE_GRAPHICS_RENDERABLECOMPONENTSFACTORY_H

#include <IComponentFactory.h>

namespace UnknownEngine {
	namespace Graphics {

		class OgreRenderSystem;

		class OgreRenderableComponentsFactory: public Core::IComponentFactory
		{
			public:
				OgreRenderableComponentsFactory(OgreRenderSystem* render_system);

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

				Core::Component* createRenderableComponent(const Core::ComponentDesc &desc);
				void destroyRenderableComponent(const Core::Component* component);

				std::unordered_set<Core::ComponentType> supported_types;
				OgreRenderSystem* render_system;
		};

	} // namespace Graphics
} // namespace UnknownEngine

#endif // UNKNOWNENGINE_GRAPHICS_RENDERABLECOMPONENTSFACTORY_H
