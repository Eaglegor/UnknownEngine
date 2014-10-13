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
#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <MessageSystem/BaseMessageListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{
	
		ThreadIndependentOgreRenderSystemBase::ThreadIndependentOgreRenderSystemBase ( const OgreRenderSubsystemDescriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
		log_helper ( log_helper ),
		engine_context(engine_context),
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
			
			if(desc.ogre_resources_filename) loadResourcesFile(desc.ogre_resources_filename.get());
			
			scene_manager = root->createSceneManager ( Ogre::ST_GENERIC );
			root->initialise ( false, desc.render_window_descriptor.window_name );

			Ogre::NameValuePairList params;
			
			if(desc.render_window_descriptor.type != OgreRenderWindowDescriptor::WindowType::OWN)
			{
				Ogre::String string_handle;

				Core::MessageSender<Graphics::GetWindowHandleMessage> sender(
					Core::MessageSystemParticipantId("OgreRenderSubsystem", Core::MessageSystemParticipantId::AutoRegistrationPolicy::AUTO_REGISTER),
																	engine_context);
				
				Graphics::GetWindowHandleMessage msg;
				msg.requested_window_name = desc.render_window_descriptor.window_name;
				msg.result_callback = [&](const NativeWindowHandleType& handle)
				{
					string_handle = Ogre::StringConverter::toString((int)(handle));
				};
				
				sender.sendMessage(msg);

				switch(desc.render_window_descriptor.type)
				{
					case OgreRenderWindowDescriptor::WindowType::EXTERNAL:
					{
						params["externalWindowHandle"] = string_handle;
						break;
					}
					case OgreRenderWindowDescriptor::WindowType::PARENT:
					{
						params["parentWindowHandle"] = string_handle;
						break;
					}
				}
			}
			
			render_windows.emplace( desc.render_window_descriptor.window_name, root->createRenderWindow(desc.render_window_descriptor.window_title, desc.render_window_descriptor.width, desc.render_window_descriptor.height, desc.render_window_descriptor.fullscreen, &params) );
			render_windows[desc.render_window_descriptor.window_name]->setVisible(true);
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
		
		void ThreadIndependentOgreRenderSystemBase::onWindowResized ( const WindowResizedMessage& msg )
		{
			Ogre::RenderWindow *window = getRenderWindow(msg.window_name);
			if(window != nullptr)
			{
				window->resize(msg.width, msg.height);
			}
		}
		
		Ogre::RenderWindow* ThreadIndependentOgreRenderSystemBase::getRenderWindow ( const std::string& name )
		{
			auto iter = render_windows.find(name);
			if(iter == render_windows.end() ) return nullptr;
			else return iter->second;
		}

	
	} // namespace Graphics
} // namespace UnknownEngine
