/*
 * EntitiesParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#ifndef ENTITIESPARSER_H_
#define ENTITIESPARSER_H_

#include <boost/property_tree/ptree_fwd.hpp>
#include <MessageSystem/MessageListenerDesc.h>

namespace UnknownEngine
{

	namespace Core
	{
		class Properties;

		class ComponentsManager;
		class Component;
		class Entity;
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

                void loadEntities(const boost::property_tree::ptree &entities_node);

			private:

				void loadEntity(const std::string &name, const boost::property_tree::ptree &entity_node);
				Core::Component* loadComponent(Core::Entity* parent_entity, const std::string &name, const boost::property_tree::ptree &component_node);
				bool createDataProvider(const boost::property_tree::ptree &data_provider_node);

				Core::ComponentsManager* components_manager;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */

#endif /* ENTITIESPARSER_H_ */
