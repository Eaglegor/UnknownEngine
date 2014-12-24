#include <stdafx.h>

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OgreRenderSubsystem.h>
#include <Logging.h>
#include <EngineContext.h>

#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/MessageSender.h>

#include <ExportedMessages/StopEngineActionMessage.h>

#include <Listeners/OgreUpdateFrameListener.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>

#include <ExportedMessages/RenderSystem/WindowResizedMessage.h>
#include <MessageSystem/BaseMessageListener.h>

#include <MessageBuffers/InstantForwardMessageBuffer.h>
#include <MessageBuffers/OnlyLastMessageBuffer.h>

#include <OgreRenderFrameListener.h>

namespace UnknownEngine
{
	namespace Graphics
	{
	
		OgreRenderSubsystem::OgreRenderSubsystem ( const OgreRenderSubsystemDescriptor& desc, Core::ILogger* logger, Core::EngineContext* engine_context ):
		logger ( logger ),
		engine_context(engine_context),
		desc(desc)
		{
		}

		void OgreRenderSubsystem::initOgre(const std::string &subsystem_name)
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

			Ogre::NameValuePairList params;
			
			if(desc.render_window_descriptor.type != OgreRenderWindowDescriptor::WindowType::OWN)
			{
				Ogre::String string_handle;

				Core::MessageSender<Graphics::GetWindowHandleMessage> sender(subsystem_name);
				
				Graphics::GetWindowHandleMessage msg;
				msg.requested_window_name = desc.render_window_descriptor.window_name;
				msg.result_callback = [&](const NativeWindowHandleType& handle)
				{
					string_handle = std::to_string((int)(handle));
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
			
			if(desc.ogre_resources_filename) loadResourcesFile(desc.ogre_resources_filename.get());
		}

		void OgreRenderSubsystem::shutdownOgre()
		{
			LOG_INFO(logger, "Shutting down OGRE");
			root->shutdown();
			
			LOG_INFO(logger, "Deleting OGRE root");
			delete root;

			LOG_INFO(logger, "Deleting OGRE Log Manager");
			ogre_log_manager->destroyLog("DefaultLog");
			delete ogre_log_manager;
		}
		
		void OgreRenderSubsystem::onFrameUpdated ( const UnknownEngine::Core::UpdateFrameMessage& msg )
		{
			Ogre::WindowEventUtilities::messagePump();
			if(frame_listener) frame_listener->update();
			root->renderOneFrame();
		}

		OgreRenderSubsystem::~OgreRenderSubsystem()
		{
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
		
		void OgreRenderSubsystem::onWindowResized ( const WindowResizedMessage& msg )
		{
			Ogre::RenderWindow *window = getRenderWindow(msg.window_name);
			if(window != nullptr)
			{
				window->resize(msg.width, msg.height);
			}
		}
		
		Ogre::RenderWindow* OgreRenderSubsystem::getRenderWindow ( const std::string& name )
		{
			auto iter = render_windows.find(name);
			if(iter == render_windows.end() ) return nullptr;
			else return iter->second;
		}

		void OgreRenderSubsystem::start(const std::string& name)
		{
			
			listener.reset ( new Core::BaseMessageListener(name) );
			
			frame_listener.reset ( new OgreRenderFrameListener() );
			
			if ( !desc.separate_rendering_thread )
			{
				initOgre(name);
				
				{
					typedef Core::UpdateFrameMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderSubsystem::onFrameUpdated);
				}
				
				{
					typedef Graphics::WindowResizedMessage MessageType;
					typedef Utils::InstantForwardMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderSubsystem::onWindowResized);
				}
				
			}
			else
			{
				
				{
					typedef Graphics::WindowResizedMessage MessageType;
					typedef Utils::OnlyLastMessageBuffer<MessageType> BufferType;
					
					listener->createMessageBuffer<MessageType, BufferType>(this, &OgreRenderSubsystem::onWindowResized);
				}
				
				rendering_thread.reset ( new boost::thread ( [this, name]()
				{
					initOgre(name);
					addSynchronizeCallback("FlushMessageBuffers", [this](){listener->flushAllMessageBuffers();});
					root->addFrameListener ( frame_listener.get() );
					this->root->startRendering();
					root->removeFrameListener ( frame_listener.get() );
					removeSynchronizeCallback("FlushMessageBuffers");
					shutdownOgre();
					frame_listener->setFinished();
				} ) );
			}
			
			if(listener) listener->registerAtDispatcher();
		}
		
		void OgreRenderSubsystem::stop()
		{
			if(listener) listener->unregisterAtDispatcher();

			if ( desc.separate_rendering_thread )
			{
				frame_listener->stopRendering();
				LOG_INFO( logger, "Waiting for OGRE shutdown");
				frame_listener->waitUntilFinished();
				LOG_INFO( logger, "Ogre shut down");
			}
			else
			{
				shutdownOgre();
			}
			
			frame_listener.reset();
			
		}
		
		void OgreRenderSubsystem::addSynchronizeCallback ( const std::string& name, const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addSynchronizeCallback ( name, callback );
		}
		
		void OgreRenderSubsystem::removeSynchronizeCallback ( const std::string& name )
		{
			if(frame_listener) frame_listener->removeSynchronizeCallback ( name );
		}
		
		void OgreRenderSubsystem::addInitCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addInitCallback ( callback );
		}
		
		void OgreRenderSubsystem::addShutdownCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addShutdownCallback ( callback );
		}
		
		void OgreRenderSubsystem::addRemoveCallback ( const std::function< void() >& callback )
		{
			if(frame_listener) frame_listener->addRemoveCallback ( callback );
		}
	
	} // namespace Graphics
} // namespace UnknownEngine
