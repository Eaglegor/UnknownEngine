#include <stdafx.h>

#include <Ogre.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>
#include <EngineContext.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/StopEngineActionMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{

		OgreRenderSubsystem::OgreRenderSubsystem ( const UnknownEngine::Graphics::OgreRenderSubsystem::Descriptor& desc, UnknownEngine::Core::LogHelper* log_helper )
			: log_helper ( log_helper )
		{

			ogre_log_manager = new Ogre::LogManager;
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
			
			if(desc.ogre_resources_filename.is_initialized()) loadResourcesFile(desc.ogre_resources_filename.get());
			
			scene_manager = root->createSceneManager ( Ogre::ST_GENERIC );
			render_window = root->initialise ( true, desc.render_window_name );
		}

		void OgreRenderSubsystem::onFrameUpdated ( const Core::UpdateFrameMessage &msg )
		{
			//LOG_DEBUG(log_helper, "Rendering frame");
			if ( msg.stage == Core::UpdateFrameMessage::PROCESSING )
			{
				Ogre::WindowEventUtilities::messagePump();
				root->renderOneFrame();
			}

		}

		OgreRenderSubsystem::~OgreRenderSubsystem()
		{
			root->shutdown();
			delete root;

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

		
	} // namespace Graphics
} // namespace UnknownEngine
