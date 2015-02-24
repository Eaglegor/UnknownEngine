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
			for(BaseOgreComponent* component : components)
			{
				if(component->getState() == BaseOgreComponent::State::WORK)
				{
					component->_update();
				}
			}
		}
		
	}
}