#include <Factories/OgreRenderableComponentsFactory.h>
#include <Components/OgreRenderableComponent.h>
#include <Parsers/OgreRenderableDescriptorParser.h>
#include <OgreRenderSystem.h>
#include <ComponentDesc.h>

namespace UnknownEngine {
	namespace Graphics {

		OgreRenderableComponentsFactory::OgreRenderableComponentsFactory(OgreRenderSystem* render_system)
			:render_system(render_system)
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

			if(desc.type == OGRE_RENDERABLE_COMPONENT_TYPE) component = createRenderableComponent(desc);

			return component;
		}

		void OgreRenderableComponentsFactory::destroyObject(Core::Component *object)
		{
			if(object->getType() == OGRE_RENDERABLE_COMPONENT_TYPE) destroyRenderableComponent(object);
		}

		Core::Component *OgreRenderableComponentsFactory::createRenderableComponent(const Core::ComponentDesc &desc)
		{
			if(!desc.descriptor.isEmpty())
			{
				return new OgreRenderableComponent(desc.descriptor.get<OgreRenderableComponent::Descriptor>(), render_system);
			}
			else
			{
				return new OgreRenderableComponent(OgreRenderableDescriptorParser::parse(desc.creation_options), render_system);
			}
		}

		void OgreRenderableComponentsFactory::destroyRenderableComponent(const Core::Component *component)
		{
			delete component;
		}

	} // namespace Graphics
} // namespace UnknownEngine
