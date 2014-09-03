#include <stdafx.h>

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <ThreadIndependentOgreRenderSystemBase.h>
#include <LogHelper.h>
#include <EngineContext.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageSender.h>

#include <ExportedMessages/StopEngineActionMessage.h>

#include <Listeners/OgreUpdateFrameListener.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>

namespace UnknownEngine
{
	namespace Graphics
	{
	
		ThreadIndependentOgreRenderSystemBase::ThreadIndependentOgreRenderSystemBase ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
		log_helper ( log_helper ),
		engine_context(engine_context),
		update_frame_listener(nullptr),
		desc(desc)
		{
		}

		void ThreadIndependentOgreRenderSystemBase::initOgre()
		{
			
			LOG_INFO(log_helper, "Initializing OGRE");
			
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
			root->initialise ( false, desc.render_window_name );
			
			Ogre::String string_handle;
			
			Core::MessageSender<Graphics::GetWindowHandleMessage> sender(
				Core::MessageSystemParticipantId("OgreRenderSubsystem", Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
																   engine_context);
			
			Graphics::GetWindowHandleMessage msg;
			msg.requested_window_name = "";
			msg.result_callback = [&](const NativeWindowHandleType& handle)
			{
				std::cout << "Got window handle : " << handle << std::endl;
				string_handle = Ogre::StringConverter::toString(handle);
			};
			
			sender.sendMessage(msg);
			
			Ogre::NameValuePairList params;
			
			params["externalWindowHandle"] = string_handle;
			//params["externalGLControl"] = "True";
			//params["currentGLContext"] = "True";
			
			render_window = root->createRenderWindow("Hello", 800, 600, false, &params);
			render_window->setVisible(true);
		}

		void ThreadIndependentOgreRenderSystemBase::shutdownOgre()
		{
			LOG_INFO(log_helper, "Shutting down OGRE");
			root->shutdown();
			
			LOG_INFO(log_helper, "Deleting OGRE root");
			delete root;

			LOG_INFO(log_helper, "Deleting OGRE Log Manager");
			ogre_log_manager->destroyLog("DefaultLog");
			delete ogre_log_manager;
		}
		
		void ThreadIndependentOgreRenderSystemBase::onFrameUpdated ( const UnknownEngine::Core::UpdateFrameMessage& msg )
		{
			//LOG_DEBUG(log_helper, "Rendering frame");
			if ( msg.stage == Core::UpdateFrameMessage::PROCESSING )
			{
				Ogre::WindowEventUtilities::messagePump();
				root->renderOneFrame();
			}

		}

		ThreadIndependentOgreRenderSystemBase::~ThreadIndependentOgreRenderSystemBase()
		{
		}

		void ThreadIndependentOgreRenderSystemBase::loadResourcesFile ( const std::string& filename )
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
