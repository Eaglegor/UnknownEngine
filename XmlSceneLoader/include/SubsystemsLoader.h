#pragma once

#include <boost/property_tree/ptree_fwd.hpp>
#include <Exception.h>

namespace UnknownEngine
{

	namespace Core
	{
		class PluginsManager;
	}

	namespace Loader
	{

		class XmlSceneLoader;

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( InvalidSubsystemTemplate );

		class SubsystemsLoader
		{
			public:
				SubsystemsLoader ( Core::PluginsManager* plugins_manager, XmlSceneLoader* scene_loader ) :
					plugins_manager ( plugins_manager ), scene_loader ( scene_loader )
				{
				}
				virtual ~SubsystemsLoader();

				void loadSubsystems ( const boost::property_tree::ptree &node );

			private:

				void loadSubsystem ( const std::string &name, const boost::property_tree::ptree &node );

				Core::PluginsManager* plugins_manager;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
