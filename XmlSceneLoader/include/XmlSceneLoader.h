/*
 * XmlSceneLoader.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef XMLSCENELOADER_H_
#define XMLSCENELOADER_H_

#include <string>
#include <ISceneLoader.h>

namespace UnknownEngine
{
	namespace Loader
	{

		class TemplatesManager;
		class ConstantsHolder;

		class XmlSceneLoader: public ISceneLoader
		{
			public:
				XmlSceneLoader(std::string filename);
				virtual ~XmlSceneLoader();

				virtual void loadScene(Core::ComponentsManager *components_manager, Core::PluginsManager* plugins_manager) override;

			private:
				void parseGlobalConstants(const boost::property_tree::ptree &root);
				void processEngineSettings(const boost::property_tree::ptree &node);
				void processSubsystems(const boost::property_tree::ptree &node, Core::PluginsManager* plugins_manager);
				void processEntities(const boost::property_tree::ptree &node, Core::ComponentsManager* components_manager);


				std::string filename;
				TemplatesManager* templates_manager;
				ConstantsHolder* constants_holder;

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */

#endif /* XMLSCENELOADER_H_ */
