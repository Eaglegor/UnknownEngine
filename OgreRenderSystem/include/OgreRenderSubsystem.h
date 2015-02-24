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
			
			virtual void initComponent(BaseOgreComponent* component) = 0;
			virtual void shutdownComponent(BaseOgreComponent* component) = 0;
			virtual void destroyComponent(BaseOgreComponent* component) = 0;
		
			Ogre::Root* getRoot(){return root;}
			Ogre::SceneManager* getSceneManager(){return scene_manager;}
			
			void onWindowCreated();
			
		protected:
			std::unordered_set<BaseOgreComponent*> components;
			
		private:
			void loadResourcesFile ( const std::string& filename );
			
			OgreRenderSubsystemDescriptor desc;
			Core::LogHelper logger;
			
			Ogre::LogManager* ogre_log_manager;
			Ogre::Root* root;
			Ogre::SceneManager* scene_manager;
			
			bool resources_initialized;
		};
	}
}