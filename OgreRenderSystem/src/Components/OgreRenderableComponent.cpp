#include <stdafx.h>

#include <Ogre.h>
#include <Components/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>

namespace UnknownEngine {
	namespace Graphics {

		void OgreRenderableComponent::init(const Core::Entity *parent_entity)
		{
			entity = render_system->getSceneManager()->createEntity(name+".Entity", mesh_data_provider->getResource().getData<Ogre::MeshPtr>());
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
			  name(name),
			  mesh_data_provider(desc.mesh_data_provider)
		{
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			mesh_data_provider->release();
			render_system->getSceneManager()->destroySceneNode(scene_node);
			render_system->getSceneManager()->destroyEntity(entity);
		}

	} // namespace Graphics
} // namespace UnknownEngine
