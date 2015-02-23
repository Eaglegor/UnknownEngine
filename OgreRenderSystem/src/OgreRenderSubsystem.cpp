#include <OgreRenderSubsystem.h>
#include <Components/BaseOgreComponent.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreConfigFile.h>
#include <OgreGpuProgramManager.h>
#include <Logging.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		
		OgreRenderSubsystem::OgreRenderSubsystem ( const char* name, const OgreRenderSubsystemDescriptor& desc ) : 
		BaseComponent ( name ),
		desc(desc),
		logger(name, desc.log_level),
		root(nullptr),
		scene_manager(nullptr),
		ogre_log_manager(nullptr),
		resources_initialized(false)
		{
		}

		OgreRenderSubsystem::~OgreRenderSubsystem ()
		{
		}
		
		void OgreRenderSubsystem::init ( const Core::IEntity* parent_entity )
		{
			LOG_INFO(logger, "Initializing OGRE");
			
			ogre_log_manager = new Ogre::LogManager();
			ogre_log_manager->createLog(desc.ogre_log_filename, true, false, false);

			root = new Ogre::Root ( desc.ogre_plugins_filename, desc.ogre_config_filename, desc.ogre_log_filename );
			
			if(desc.show_config_dialog)
			{
				root->showConfigDialog();
			}
			else
			{
				if(!root->restoreConfig())
				{
					root->showConfigDialog();
				}
			}
			
			scene_manager = root->createSceneManager ( Ogre::ST_GENERIC );
			root->initialise ( false );
			
		}

		void OgreRenderSubsystem::onWindowCreated()
		{
			if(!resources_initialized)
			{
				if(desc.ogre_resources_filename) loadResourcesFile(desc.ogre_resources_filename.get());
				resources_initialized = true;
			}
		}
		
		void OgreRenderSubsystem::shutdown()
		{
			LOG_INFO(logger, "Shutting down OGRE");
			root->shutdown();
			
			LOG_INFO(logger, "Deleting OGRE root");
			delete root;

			LOG_INFO(logger, "Deleting OGRE Log Manager");
			ogre_log_manager->destroyLog("DefaultLog");
			delete ogre_log_manager;
		}

		void OgreRenderSubsystem::loadResourcesFile ( const std::string& filename )
		{
			Ogre::ConfigFile cf;
			cf.load(filename);
		
			// Go through all sections & settings in the file
			Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
		
			Ogre::String secName, typeName, archName;
			while (seci.hasMoreElements())
			{
				secName = seci.peekNextKey();
				Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
				Ogre::ConfigFile::SettingsMultiMap::iterator i;
				for (i = settings->begin(); i != settings->end(); ++i)
				{
					typeName = i->first;
					archName = i->second;
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
						archName, typeName, secName);
				}
			}

			Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		}
		
		void OgreRenderSubsystem::onUpdateFrame ( Math::Scalar dt )
		{
			{
				std::lock_guard<LockPrimitive> guard(initializing_components_lock);
				size_t count = initializing_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = initializing_components.front();
					initializing_components.pop();
					if(component->getState() == BaseOgreComponent::State::INITIALIZATION)
					{
						component->_init();
						components.emplace(component);
					}
					else
					{
						initializing_components.push(component);
					}
				}
			}
			
			for(BaseOgreComponent* component : components)
			{
				if(component->getState() == BaseOgreComponent::State::WORK)
				{
					component->_update();
				}
			}
			
			{
				std::lock_guard<LockPrimitive> guard(shutting_down_components_lock);
				size_t count = shutting_down_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = shutting_down_components.front();
					shutting_down_components.pop();
					if(component->getState() == BaseOgreComponent::State::SHUTTING_DOWN)
					{
						component->_shutdown();
						components.erase(component);
					}
					else
					{
						shutting_down_components.push(component);
					}
				}
			}
			
			{
				std::lock_guard<LockPrimitive> guard(destructing_components_lock);
				size_t count = destructing_components.size();
				for(int i = 0; i < count; ++i)
				{
					BaseOgreComponent* component = destructing_components.front();
					destructing_components.pop();
					if(component->getState() == BaseOgreComponent::State::DELETION)
					{
						component->_destroy();
					}
					else
					{
						destructing_components.push(component);
					}
				}
			}
			
		}
		
		void OgreRenderSubsystem::initComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(initializing_components_lock);
			initializing_components.push(component);
		}

		void OgreRenderSubsystem::shutdownComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(shutting_down_components_lock);
			shutting_down_components.push(component);
		}
		
		void OgreRenderSubsystem::destroyComponent ( BaseOgreComponent* component )
		{
			std::lock_guard<LockPrimitive> guard(destructing_components_lock);
			destructing_components.push(component);
		}
		
	}
}