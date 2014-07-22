#include <stdafx.h>

#include <Components/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>

namespace UnknownEngine {
	namespace Graphics {

		void OgreRenderableComponent::init(const Core::Entity *parent_entity)
		{
			entity = render_system->getSceneManager()->createEntity(name+".Entity", nullptr);
			scene_node = render_system->getSceneManager()->getRootSceneNode()->createChildSceneNode(this->name+".SceneNode");
		}

		void OgreRenderableComponent::start()
		{
			scene_node->attachObject(entity);
		}

		void OgreRenderableComponent::shutdown()
		{
			scene_node->detachObject(entity->getName());
		}

		Core::ComponentType OgreRenderableComponent::getType()
		{
			return type;
		}

		OgreRenderableComponent::OgreRenderableComponent(const std::string &name, const Descriptor &desc, OgreRenderSubsystem *render_system)
			:render_system(render_system),
			  type(OGRE_RENDERABLE_COMPONENT_TYPE),
			  name(name)
		{
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			render_system->getSceneManager()->destroySceneNode(scene_node);
			render_system->getSceneManager()->destroyEntity(entity);
		}

	} // namespace Graphics
} // namespace UnknownEngine
