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
	 
	boost::program_options::positional_options_description p;
	p.add("scene", -1);
		  
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options_desc), vm);
	boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options_desc).positional(p).run(), vm);
	boost::program_options::notify(vm);
	
	
	Properties props;
	props.set<float>("f1", 1);
	props.set<float>("f2", 2);
	props.set<float>("f3", 3);
	props.set<std::string>("s1", "111");
	props.set<std::string>("s2", "222");
	props.set<std::string>("s3", "333");
	
	props.set< std::pair<int,int> >("p1", std::make_pair(1, 1));
	props.set< std::pair<int,int> >("p2", std::make_pair(2, 2));
	props.set< std::pair<int,int> >("p3", std::make_pair(3, 3));
	
	Properties::Iterator<float> float_iter;
	Properties::Iterator<std::string> string_iter;
	Properties::Iterator< std::pair<int,int> > pair_iter;
	
	for(float_iter = props.begin<float>(); float_iter!=props.end<float>(); ++float_iter)
	{
		std::cout << float_iter->first << " = " << *float_iter->second << std::endl;
	}
	
	for(string_iter = props.begin<std::string>(); string_iter!=props.end<std::string>(); ++string_iter)
	{
		std::cout << string_iter->first << " = " << *string_iter->second << std::endl;
	}
	
	for(pair_iter = props.begin< std::pair<int,int> >(); pair_iter!=props.end< std::pair<int,int> >(); ++pair_iter)
	{
		std::cout << pair_iter->first << " = " << pair_iter->second->first << ", " << pair_iter->second->second << std::endl;
	}
	
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
