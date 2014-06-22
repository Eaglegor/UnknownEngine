/*
 * SubsystemsParser.h
 *
 *  Created on: 22 ���� 2014 �.
 *      Author: Eaglegor
 */

#ifndef SUBSYSTEMSPARSER_H_
#define SUBSYSTEMSPARSER_H_

#include <boost/property_tree/ptree.hpp>

namespace UnknownEngine
{

	namespace Core
	{
		class PluginsManager;
	}

	namespace Loader
	{

		class XmlSceneLoader;

		class SubsystemsLoader
		{
			public:
				SubsystemsLoader(Core::PluginsManager* plugins_manager, XmlSceneLoader* scene_loader) :
						plugins_manager(plugins_manager), scene_loader(scene_loader)
				{
				}
				virtual ~SubsystemsLoader();

				void loadSubsystems(const boost::property_tree::ptree &node);

			private:

				void loadSubsystem(std::string name, const boost::property_tree::ptree &node);

				Core::PluginsManager* plugins_manager;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* SUBSYSTEMSPARSER_H_ */
