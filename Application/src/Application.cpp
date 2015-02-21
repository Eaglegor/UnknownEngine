#include <stdafx.h>
#include <StressTest.h>

#include <Engine.h>
#include <XmlSceneLoader.h>
#include <boost/program_options.hpp>

using namespace UnknownEngine::Core;
using namespace UnknownEngine::Loader;

int main ( int argc, char** argv )
{
	boost::program_options::options_description options_desc ( "Allowed options" );
	options_desc.add_options()
	( "scene", boost::program_options::value<std::string>()->value_name ( "filename" ), "specify the scene file" )
	( "help", "help message" );

	boost::program_options::positional_options_description p;
	p.add ( "scene", -1 );

	boost::program_options::variables_map vm;
	boost::program_options::store ( boost::program_options::parse_command_line ( argc, argv, options_desc ), vm );
	boost::program_options::store ( boost::program_options::command_line_parser ( argc, argv ).options ( options_desc ).positional ( p ).run(), vm );
	boost::program_options::notify ( vm );

	if ( vm.count ( "help" ) )
	{
		std::cout << options_desc << std::endl;
		return 1;
	}

	Engine engine;
	engine.init();

	IComponent* main_loop = engine.getContext().getComponentsManager()->findComponent(MAIN_LOOP_COMPONENT_NAME);
	StressTest test(main_loop);

	if ( vm.count ( "scene" ) )
	{
		std::string scene_name = vm["scene"].as<std::string>();
		XmlSceneLoader loader ( &engine.getContext(), engine.getPluginsManager() );
		loader.loadScene(scene_name);
		
		if(scene_name == "StressTestScene.xml")
		{
			test.init ( &engine.getContext() );
		}
	}

	engine.start();

	test.shutdown();

	engine.shutdown();

	return 0;
}
