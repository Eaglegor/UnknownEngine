#include <iostream>

#include <MainLoop/MainLoop.h>
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderSystemUpdateFrameListener.h>
#include <Plugins/PluginsManager.h>
#include <Plugins/PluginError.h>

#include <ComponentManager.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>
#include <MessageSystem/SenderInfo.h>

#include <ExportedMessages/RenderSystem/CreateRenderWindowMessage.h>
#include <ExportedMessages/UpdateFrameMessage.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Graphics;

int main ()
{

	try
	{

		ComponentManager::getSingleton();
		MessageDispatcher::getSingleton();
		MessageDictionary::getSingleton();

		PluginsManager mgr;

		MessageDictionary::getSingleton()->registerNewMessageType(CreateRenderWindowMessage::MSG_TYPE_NAME);
		MessageDictionary::getSingleton()->registerNewMessageType(UpdateFrameMessage::MSG_TYPE_NAME);

		mgr.installPlugin ( "DirectX11RenderSystem.dll" );
		mgr.initPlugins();

		CreateRenderWindowMessage msg;
		msg.window_desc.fullscreen = false;
		msg.window_desc.width = 800;
		msg.window_desc.height = 600;
		msg.window_desc.title = "Hello";

		MessageDispatcher::getSingleton()->deliverMessage( CreateRenderWindowMessagePacker(SenderInfo("Core")).packMessage(msg) );

		MainLoop main_loop;
		main_loop.start();

	}
	catch ( const PluginError &err )
	{
		std::cout << "Error while loading plugin: " << err.what () << std::endl;
	}

	return 0;
}
