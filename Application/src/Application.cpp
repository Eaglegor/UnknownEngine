#include <stdafx.h>

#include <Engine.h>
#include <XmlSceneLoader.h>
#include <ConstantsHolder.h>
#include <EngineContext.h>
#include <MessageSystem/MessageListenerDesc.h>
#include <Plugins/PluginsManager.h>
#include <SubsystemDesc.h>
#include <boost/program_options.hpp>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main(int argc, char** argv)
{
	boost::program_options::options_description options_desc("Allowed options");
	options_desc.add_options()
	  ("scene", boost::program_options::value<std::string>()->value_name("filename"), "specify the scene file")
	  ("help", "help message");
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options_desc), vm);
	boost::program_options::notify(vm);
	
	if(vm.count("help"))
	{
	  std::cout << options_desc << std::endl;
	  return 1;
	}

	Engine engine;
	engine.init();
	
	if(vm.count("scene"))
	{
	  XmlSceneLoader loader(&engine.getContext(), engine.getPluginsManager());
	  loader.loadScene(vm["scene"].as<std::string>());
	}
	
	engine.start();

	engine.shutdown();
	
	return 0;
}
