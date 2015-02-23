#pragma once

#include <ComponentSystem/BaseComponent.h>
#include <Descriptors/OgreRenderSubsystemDescriptor.h>
#include <ComponentInterfaces/Engine/UpdateFrameListenerComponent.h>
#include <LogHelper.h>
#include <unordered_set>
#include <queue>

namespace Ogre
{
	class LogManager;
	class Root;
	class SceneManager;
}

namespace UnknownEngine
{

	namespace Graphics
	{

		class BaseOgreComponent;
		class OgreRenderSubsystem : 
			public Core::BaseComponent,
			public ComponentInterfaces::UpdateFrameListenerComponent
		{
		public:
			OgreRenderSubsystem(const char* name, const OgreRenderSubsystemDescriptor &desc);
			~OgreRenderSubsystem();
			
			virtual void init ( const Core::IEntity* parent_entity ) override;
			virtual void shutdown() override;
			
			virtual void onUpdateFrame(Math::Scalar dt) override;
			
			void initComponent(BaseOgreComponent* component);
			void shutdownComponent(BaseOgreComponent* component);
			void destroyComponent(BaseOgreComponent* component);
		
			Ogre::Root* getRoot(){return root;}
			Ogre::SceneManager* getSceneManager(){return scene_manager;}
			
		private:
			void loadResourcesFile ( const std::string& filename );
			
			OgreRenderSubsystemDescriptor desc;
			Core::LogHelper logger;
			
			std::unordered_set<BaseOgreComponent*> components;
			std::queue<BaseOgreComponent*> initializing_components;
			std::queue<BaseOgreComponent*> shutting_down_components;
			std::queue<BaseOgreComponent*> destructing_components;
			
			typedef std::mutex LockPrimitive;
			LockPrimitive initializing_components_lock;
			LockPrimitive shutting_down_components_lock;
			LockPrimitive destructing_components_lock;
			
			Ogre::LogManager* ogre_log_manager;
			Ogre::Root* root;
			Ogre::SceneManager* scene_manager;
		};
	}
}