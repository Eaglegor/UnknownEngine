#pragma once

#include <Components/BaseOgreComponent.h>
#include <Descriptors/OgreHOQVisibilityCheckerDesc.h>
#include <ComponentInterfaces/RenderSystem/Common/VerboseVisibilityChecker.h>
#include <ComponentInterfaces/RenderSystem/Ogre/IOgreRenderableComponent.h>
#include <ComponentInterfaces/RenderSystem/Ogre/IOgreRenderWindowComponent.h>
#include <ComponentSystem/ComponentInterfacePtr.h>
#include <Concurrency/DataStructures/ConcurrentSet.h>

#include <LogHelper.h>

#include <OgreMaterial.h>
#include <OgreRenderObjectListener.h>
#include <OgreRenderQueueListener.h>
#include <OgreRenderTargetListener.h>
#include <unordered_set>

namespace Ogre
{
	class HardwareOcclusionQuery;
	class SceneNode;
	class Entity;
}

namespace UnknownEngine
{
	namespace Graphics
	{
		class OgreHOQVisibilityChecker:
		public BaseOgreComponent,
		public ComponentInterfaces::VerboseVisibilityChecker,
		public Ogre::RenderObjectListener,
		public Ogre::RenderQueueListener,
		public Ogre::RenderTargetListener
		{
		public:
			OgreHOQVisibilityChecker(const char* name, const OgreHOQVisibilityCheckerDesc &desc, OgreRenderSubsystem* render_subsystem);
			
			constexpr static const char* getTypeName(){return "Ogre.HOQVisibilityChecker";}
			virtual Core::ComponentType getType() const {return getTypeName();}
			
			virtual void internalInit() override;
			virtual void internalShutdown() override;
			
			virtual void _update() override;
			
			virtual ComponentInterfaces::VisibilityData getVisibilityData() const override;
			virtual bool isVisible() const override;
			
			virtual void addListener ( ComponentInterfaces::VisibilityCheckerListener* listener ) override;
			virtual void removeListener ( ComponentInterfaces::VisibilityCheckerListener* listener ) override;
			
			virtual void notifyRenderSingleObject ( Ogre::Renderable* rend, const Ogre::Pass* pass, const Ogre::AutoParamDataSource* source, const Ogre::LightList* pLightList, bool suppressRenderStateChanges );
			
			virtual void renderQueueEnded ( Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation );
			
			virtual void preRenderQueues();
			virtual void postRenderQueues();
			
		private:
			
			bool objectIsNotRendered();
			
			OgreHOQVisibilityCheckerDesc desc;
			ComponentInterfaces::VisibilityData current_visibility_data;
			Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderableComponent> checkable_object;
			Core::ComponentInterfacePtr<ComponentInterfaces::IOgreRenderWindowComponent> render_window;
			
			Utils::ConcurrentSet<ComponentInterfaces::VisibilityCheckerListener*> listeners;
			
			Ogre::HardwareOcclusionQuery* area_query;
			Ogre::HardwareOcclusionQuery* visible_part_query;
			Ogre::HardwareOcclusionQuery* active_query;
			
			Ogre::MaterialPtr area_material;
			Ogre::MaterialPtr visible_part_material;
			
			Ogre::Entity* area_entity;
			Ogre::Entity* visible_part_entity;
			
			Ogre::SceneNode* scene_node;
			
			Ogre::Renderable* area_renderable;
			Ogre::Renderable* visible_part_renderable;
			
			bool area_query_is_running;
			bool visible_part_query_is_running;
			
			Core::LogHelper logger;
			
			bool render_target_active;
		};
	}
}