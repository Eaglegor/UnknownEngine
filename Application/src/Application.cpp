#include <iostream>
#include <Engine.h>
#include <XmlSceneLoader.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main()
{

	Engine engine;

	XmlSceneLoader loader;
	engine.init();
	engine.loadScene(&loader);
	engine.start();

	return 0;
}
