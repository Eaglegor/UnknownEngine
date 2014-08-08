/*
 * EntitiesParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <boost/property_tree/ptree_fwd.hpp>

namespace UnknownEngine
{

	namespace Core
	{
		class Properties;

		class EngineContext;
		class Component;
		class Entity;
	}

	namespace Loader
	{
		class XmlSceneLoader;

		class EntitiesLoader
		{
			public:
				EntitiesLoader ( Core::EngineContext* engine_context, XmlSceneLoader* scene_loader ) :
					engine_context ( engine_context ), scene_loader ( scene_loader )
				{
				}

				virtual ~EntitiesLoader();

				void loadEntities ( const boost::property_tree::ptree &entities_node );

			private:

				void loadEntity ( const std::string &name, const boost::property_tree::ptree &entity_node );
				Core::Component* loadComponent ( Core::Entity* parent_entity, const std::string &name, const boost::property_tree::ptree &component_node );
				bool createDataProvider ( const boost::property_tree::ptree &data_provider_node );

				Core::EngineContext* engine_context;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
