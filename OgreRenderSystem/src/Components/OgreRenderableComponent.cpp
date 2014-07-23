#include <stdafx.h>

#include <Ogre.h>
#include <Components/OgreRenderableComponent.h>
#include <OgreRenderSubsystem.h>
#include <DataProviders/OgreMeshPtrProvider.h>
#include <Listeners/OgreRenderableComponentListener.h>
#include <EngineContext.h>

namespace UnknownEngine {
	namespace Graphics {

		void OgreRenderableComponent::init(const Core::Entity *parent_entity)
		{
			entity = render_system->getSceneManager()->createEntity(getName()+".Entity", mesh_data_provider->getResource().getData<Ogre::MeshPtr>());
			scene_node = render_system->getSceneManager()->getRootSceneNode()->createChildSceneNode(getName()+".SceneNode");
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

		void OgreRenderableComponent::onTransformChanged(const Core::TransformChangedMessage &message)
		{

		}

		void OgreRenderableComponent::doChangeMaterial(const ChangeMaterialActionMessage &message)
		{

		}

		OgreRenderableComponent::OgreRenderableComponent(const std::string &name, const Descriptor &desc, OgreRenderSubsystem *render_system, Core::EngineContext *engine_context)
			: Core::Component(name),
			  render_system(render_system),
			  type(OGRE_RENDERABLE_COMPONENT_TYPE),
			  mesh_data_provider(desc.mesh_data_provider)
		{
		}

		OgreRenderableComponent::~OgreRenderableComponent()
		{
			mesh_data_provider->release();
			render_system->getSceneManager()->destroySceneNode(scene_node);
			render_system->getSceneManager()->destroyEntity(entity);
		}

		Core::IMessageListener *OgreRenderableComponent::createListener(const std::string &listener_name, Core::EngineContext* engine_context)
		{
			listeners.emplace_back(getName()+".Listeners."+listener_name, this, engine_context);
			return &listeners.back();
		}

	} // namespace Graphics
} // namespace UnknownEngine
