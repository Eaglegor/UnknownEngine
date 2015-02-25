#include <OgreRoot.h>
#include <OgreRenderWindowComponent.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <MessageSystem/MessageSender.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgreRenderWindowComponent::OgreRenderWindowComponent (const char* name, const OgreRenderWindowDescriptor& desc, OgreRenderSubsystem* render_subsystem):
		BaseOgreComponent(name, render_subsystem),
		desc(desc),
		logger(name, desc.log_level),
		render_subsystem(render_subsystem),
		parent_window(desc.parent_window)
		{
			Core::ComponentsManager::getSingleton()->reserveComponent(render_subsystem);
		}

		void OgreRenderWindowComponent::internalInit ()
		{
			root = render_subsystem->getRoot();
			
			Ogre::NameValuePairList params;
			
			if(desc.type != OgreRenderWindowDescriptor::WindowType::OWN && parent_window)
			{
				Ogre::String string_handle = std::to_string((int)parent_window->getWindowHandle());

				switch(desc.type)
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
				
				parent_window->addWindowEventsListener(this);
			}
			
			render_window = root->createRenderWindow(desc.window_title, desc.width, desc.height, desc.fullscreen, &params);
			render_window->setVisible(true);
			render_subsystem->onWindowCreated();
		}

		void OgreRenderWindowComponent::internalShutdown()
		{
			if(parent_window && desc.type != OgreRenderWindowDescriptor::WindowType::OWN){
				parent_window->removeWindowEventsListener(this);
			}
			
			root->getRenderSystem()->destroyRenderWindow(render_window->getName());
		}

		void OgreRenderWindowComponent::onWindowResized ( size_t new_width, size_t new_height )
		{
			render_window->resize(new_width, new_height);
		}
		
		void OgreRenderWindowComponent::onWindowClosed()
		{
			// Perhaps some internal shutdown?
		}
		
		OgreRenderWindowComponent::~OgreRenderWindowComponent()
		{
			Core::ComponentsManager::getSingleton()->releaseComponent(render_subsystem);
		}
		
		Core::IComponentInterface* OgreRenderWindowComponent::getInterface ( const Core::ComponentType& type )
		{
			if(type == ComponentInterfaces::IOgreRenderWindowComponent::getTypeName()) return static_cast<ComponentInterfaces::IOgreRenderWindowComponent*>(this);
			return nullptr;
		}
		
	}
}