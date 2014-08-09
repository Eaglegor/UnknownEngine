/*
 * EntitiesParser.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <boost/property_tree/ptree_fwd.hpp>
#include <unordered_map>

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

		class IDataProvider;
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

				std::unordered_map<std::string, Loader::IDataProvider*> data_providers;
				
				Core::EngineContext* engine_context;
				XmlSceneLoader* scene_loader;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
