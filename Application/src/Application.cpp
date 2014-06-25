#include <iostream>
#include <Engine.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main()
{
	Engine engine;

    XmlSceneLoader loader("LHEScene.xml");
	engine.init();
	engine.loadScene(&loader);
	engine.start();

	return 0;
}
