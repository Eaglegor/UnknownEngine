#include <stdafx.h>

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OgreRenderSubsystem.h>
#include <LogHelper.h>
#include <EngineContext.h>

#include <MessageSystem/MessageSystemParticipantDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

#include <ExportedMessages/StopEngineActionMessage.h>

#include <Listeners/OgreUpdateFrameListener.h>

#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
#include <OgreRenderCallback.h>
#endif

namespace UnknownEngine
{
	namespace Graphics
	{
	
		OgreRenderSubsystem::OgreRenderSubsystem ( const OgreRenderSubsystem::Descriptor& desc, Core::LogHelper* log_helper, Core::EngineContext* engine_context ):
		log_helper ( log_helper ),
		engine_context(engine_context),
		update_frame_listener(nullptr),
		desc(desc)
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

		void OgreRenderSubsystem::start()
		{
			#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			if(!desc.separate_rendering_thread)
			{
			#endif
				LOG_INFO ( log_helper, "Registering update frame listener..." );
				update_frame_listener = new OgreUpdateFrameListener ( "Graphics.Ogre.Listeners.UpdateFrameListener", this );
				engine_context->getMessageDispatcher()->addListener ( Core::UpdateFrameMessage::getTypeName(), update_frame_listener );
				
			#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			}
			else
			{
				render_synchronize_callback.reset(new OgreRenderCallback());
				
				root->addFrameListener(render_synchronize_callback.get());
				rendering_thread.reset( new boost::thread( [&](){root->startRendering();} ) );
			}
			#endif
		}

		void OgreRenderSubsystem::stop()
		{
			LOG_INFO ( log_helper, "Unregistering update frame listener" );
			if(update_frame_listener != nullptr)
			{
				engine_context->getMessageDispatcher()->removeListener ( update_frame_listener );
				delete update_frame_listener;
			}
			
			#ifdef ENABLE_OGRE_SEPARATE_THREAD_RENDERING
			if(desc.separate_rendering_thread)
			{
				render_synchronize_callback->stopRendering();
				render_synchronize_callback->waitUntilFinished();
				render_synchronize_callback.reset();
			}
			#endif
			
		}

		void OgreRenderSubsystem::addInitCallback ( const std::string& name, const std::function< void() >& callback )
		{
			if(render_synchronize_callback != nullptr) render_synchronize_callback->addInitCallback(name, callback);
		}

		void OgreRenderSubsystem::addRemoveCallback ( const std::string& name, const std::function< void() >& callback )
		{
			if(render_synchronize_callback != nullptr) render_synchronize_callback->addRemoveCallback(name, callback);
		}

		void OgreRenderSubsystem::addSynchronizeCallback ( const std::string& name, const std::function< void() >& callback )
		{
			if(render_synchronize_callback != nullptr) render_synchronize_callback->addSynchronizeCallback(name, callback);
		}

		void OgreRenderSubsystem::removeSynchronizeCallback ( const std::string& name )
		{
			if(render_synchronize_callback != nullptr) render_synchronize_callback->removeSynchronizeCallback(name);
		}

		
	} // namespace Graphics
} // namespace UnknownEngine
