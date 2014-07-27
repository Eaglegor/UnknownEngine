#include <stdafx.h>

#include <Engine.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>
#include <EngineContext.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Plugins/PluginsManager.h>
#include <SubsystemDesc.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main()
{
	Engine engine;

    //XmlSceneLoader loader("LHEScene.xml");
	engine.init();
	
	{
	  SubsystemDesc desc;
	  desc.name = "Logger";
	  desc.module_name = "libConsoleLogger.so";
	  
	  ReceivedMessageDesc msg;
	  msg.message_type_name = "Engine.LogMessage";
	  
	  desc.received_messages.push_back(msg);
	  
	  engine.getPluginsManager()->loadSubsystem(desc);
	}
	
	{
	  SubsystemDesc desc;
	  desc.name = "Render";
	  desc.module_name = "libOgreRenderSystem.so";
	  desc.creation_options.set<std::string>("render_window_name", "Hello");
	  
	  ReceivedMessageDesc msg;
	  msg.message_type_name = "Engine.MainLoop.UpdateFrameMessage";
	  
	  desc.received_messages.push_back(msg);
	  
	  engine.getPluginsManager()->loadSubsystem(desc);
	}
	
	//engine.loadScene(&loader);
	engine.start();

	return 0;
}
