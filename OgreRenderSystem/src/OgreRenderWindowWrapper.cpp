#include <OgreRenderWindowWrapper.h>
#include <OgreRoot.h>
#include <ExportedMessages/RenderSystem/GetWindowHandleMessage.h>
#include <MessageSystem/MessageSender.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		OgreRenderWindowWrapper::OgreRenderWindowWrapper (OgreRenderSubsystem* render_subsystem, OgreRenderWindowDescriptor& desc ):
		render_subsystem(render_subsystem)
		{
			Ogre::Root* root = render_subsystem->getOgreRoot();
			
			Ogre::NameValuePairList params;
			
			if(desc.type != OgreRenderWindowDescriptor::WindowType::OWN)
			{
				Ogre::String string_handle;

				Core::MessageSender<Graphics::GetWindowHandleMessage> sender(render_subsystem->getName());
				
				Graphics::GetWindowHandleMessage msg;
				msg.requested_window_name = desc.window_name;
				msg.result_callback = [&](const NativeWindowHandleType& handle)
				{
					string_handle = std::to_string((int)(handle));
				};
				
				sender.sendMessage(msg);

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
			}
			
			render_window = root->createRenderWindow(desc.window_title, desc.width, desc.height, desc.fullscreen, &params);
		}

		OgreRenderWindowWrapper::~OgreRenderWindowWrapper()
		{
			render_subsystem->getOgreRoot()->getRenderSystem()->destroyRenderWindow(render_window->getName());
		}
		
	}
}