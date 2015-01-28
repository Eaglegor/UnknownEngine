#include <stdafx.h>

#include <OgreCEGuiSubsystem.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <MessageSystem/MessageSender.h>
#include <../OgreRenderSystem/include/ExportedMessages/OgreRenderSystem/GetOgreRenderTargetMessage.h>
#include <ExportedMessages/OgreRenderSystem/GetOgreRenderTargetMessage.h>

namespace UnknownEngine
{
	namespace GUI
	{
		OgreCEGuiSubsystem::OgreCEGuiSubsystem ( const char* name, const Core::LogHelper& logger ):
		logger(logger),
		name(name)
		{
		}
		
		OgreCEGuiSubsystem::~OgreCEGuiSubsystem()
		{
		}

		void OgreCEGuiSubsystem::init()
		{
			Core::MessageSender<Graphics::GetOgreRenderTargetMessage> sender(name);
			Graphics::GetOgreRenderTargetMessage msg;
			msg.render_target_name = "TestWindow";
			msg.value_return_callback = [&](Ogre::RenderTarget* render_target)
			{
				LOG_INFO(logger, "Creating CEGUI renderer");
				renderer = &CEGUI::OgreRenderer::bootstrapSystem(*render_target);
				LOG_INFO(logger, "CEGUI renderer created");
			};
			sender.sendMessage(msg);
		}

		void OgreCEGuiSubsystem::shutdown()
		{
			
		}
		
	}
}