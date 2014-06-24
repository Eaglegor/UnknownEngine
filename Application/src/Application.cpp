#include <iostream>
#include <Engine.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main()
{
	Engine engine;

	ConstantsHolder c;
	c.pushScope();

	c.setConstantValue("Const1", "!RC1!");
	c.setConstantValue("Const2", "!RC2!");
	c.setConstantValue("Const3", "!RC3!");

	std::string in = "Constant1: ${Const1}, Constant2: ${Const2}, Constant3: ${Const3}";

	std::string out = c.applyPlaceholderConstants(in);

	std::cout << out << std::endl;

    XmlSceneLoader loader("LHEScene.xml");
	engine.init();
	engine.loadScene(&loader);
	engine.start();

	return 0;
}
