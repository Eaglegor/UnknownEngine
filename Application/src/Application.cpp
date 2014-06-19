#include <iostream>

#include <MainLoop/MainLoop.h>
#include <RenderSystem/RenderSystem.h>
#include <RenderSystem/RenderSystemMainLoopListener.h>
#include <Plugins/PluginsManager.h>
#include <Plugins/PluginError.h>

#include <ComponentManager.h>
#include <MessageSystem/MessageDictionary.h>
#include <MessageSystem/MessageDispatcher.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Graphics;

int main ()
{

	PluginsManager mgr;

	try
	{

		ComponentManager::getSingleton();
		MessageDispatcher::getSingleton();
		MessageDictionary::getSingleton();

		mgr.loadPlugin ( "libDirectX11RenderSystem.dll" );

		RenderSystem* rs = mgr.getRenderSystem ( 0 );
		RenderWindowDesc desc;
		desc.fullscreen = false;
		desc.width = 800;
		desc.height = 600;
		desc.title = "Hello";
		rs->createRenderWindow ( desc );

		RenderSystemMainLoopListener render_system_listener(rs);
		MessageDispatcher::getSingleton()->addListener( "Engine.UpdateFrame", &render_system_listener );

		MainLoop main_loop;

		main_loop.start();

	}
	catch ( const PluginError &err )
	{
		std::cout << "Error while loading plugin: " << err.what () << std::endl;
	}

	return 0;
}
