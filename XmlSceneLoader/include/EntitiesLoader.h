/*
 * EntitiesParser.h
 *
 *  Created on: 22 θώνÿ 2014 γ.
 *      Author: Eaglegor
 */

#ifndef ENTITIESPARSER_H_
#define ENTITIESPARSER_H_

#include <boost/property_tree/ptree.hpp>

namespace UnknownEngine
{

	namespace Core
	{
		class ComponentsManager;
	}

	namespace Loader
	{

		class XmlSceneLoader;

		class EntitiesLoader
		{
			public:
				EntitiesLoader(Core::ComponentsManager* components_manager, XmlSceneLoader* scene_loader) :
						components_manager(components_manager), scene_loader(scene_loader)
				{
				}

				virtual ~EntitiesLoader();

				void loadEntities(boost::property_tree::ptree)
				{
				}

			private:
				Core::ComponentsManager* components_manager;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ENTITIESPARSER_H_ */
