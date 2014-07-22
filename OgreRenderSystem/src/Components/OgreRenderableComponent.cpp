#include <Components/OgreRenderableComponent.h>

namespace UnknownEngine {
	namespace Graphics {

		void OgreRenderableComponent::init(const Core::Entity *parent_entity)
		{

		}

		void OgreRenderableComponent::start()
		{

		}

		void OgreRenderableComponent::shutdown()
		{

		}

		Core::ComponentType OgreRenderableComponent::getType()
		{
			return type;
		}

		OgreRenderableComponent::OgreRenderableComponent(const Descriptor &desc, OgreRenderSystem *render_system)
			:render_system(render_system),
			  type(OGRE_RENDERABLE_COMPONENT_TYPE)
		{
		}

	} // namespace Graphics
} // namespace UnknownEngine
