/*
 * XmlSceneLoader.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <ISceneLoader.h>
#include <Exception.h>

namespace UnknownEngine
{
	namespace Loader
	{

		class TemplatesManager;
		class ConstantsHolder;

		UNKNOWNENGINE_SIMPLE_EXCEPTION(InvalidSceneFile);
		UNKNOWNENGINE_SIMPLE_EXCEPTION(NoTemplatesLoaded);

		class XmlSceneLoader: public ISceneLoader
		{
			public:
				XmlSceneLoader(const std::string &filename);
				virtual ~XmlSceneLoader();

				virtual void loadScene(Core::ComponentsManager *components_manager, Core::PluginsManager* plugins_manager) override;

				virtual ConstantsHolder* getConstantsHolder();
				virtual TemplatesManager* getTemplatesManager();

			private:
				void parseGlobalConstants(const boost::property_tree::ptree &root);
				void processEngineSettings(const boost::property_tree::ptree &node);
				void processSubsystems(const boost::property_tree::ptree &node, Core::PluginsManager* plugins_manager);
				void processEntities(const boost::property_tree::ptree &node, UnknownEngine::Core::ComponentsManager *components_manager);

				std::string filename;
				TemplatesManager* templates_manager;
				ConstantsHolder* constants_holder;

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */
