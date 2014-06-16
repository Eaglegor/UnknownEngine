#include <iostream>

#include <RenderSystem.h>
#include <PluginsManager.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Graphics;

int main() {

	PluginsManager mgr;
	mgr.loadPlugin("");

	RenderSystem* rs = mgr.getRenderSystem(0);
	RenderWindowDesc desc;
	desc.fullscreen = false;
	desc.width = 800;
	desc.height = 600;
	desc.title = "Hello";
	rs->createRenderWindow(desc);

	while(true);

	return 0;
}
