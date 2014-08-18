/*
 * XmlSceneLoader.h
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#pragma once

#include <string>

#include <boost/property_tree/ptree_fwd.hpp>

#include <XmlSceneLoader_export.h>
#include <ISceneLoader.h>
#include <Exception.h>

namespace UnknownEngine
{

	namespace Core
	{
		class EngineContext;
	}

	namespace Loader
	{

		class TemplatesManager;
		class ConstantsHolder;

		UNKNOWNENGINE_SIMPLE_EXCEPTION ( InvalidSceneFile );
		UNKNOWNENGINE_SIMPLE_EXCEPTION ( NoTemplatesLoaded );

		class XmlSceneLoader: public ISceneLoader
		{
			public:
				XMLSCENELOADER_EXPORT
				XmlSceneLoader ( Core::EngineContext* engine_context, Core::PluginsManager* plugins_manager );

				XMLSCENELOADER_EXPORT
				virtual ~XmlSceneLoader();

				XMLSCENELOADER_EXPORT
				virtual void loadScene ( const std::string& filename ) override;

				XMLSCENELOADER_EXPORT
				virtual ConstantsHolder* getConstantsHolder();

				XMLSCENELOADER_EXPORT
				virtual TemplatesManager* getTemplatesManager();

			private:
				void parseGlobalConstants ( const boost::property_tree::ptree &root );
				void processTemplates ( const boost::property_tree::ptree &node );
				void processSubsystems ( const boost::property_tree::ptree &node, Core::PluginsManager* plugins_manager );
				void processEntities ( const boost::property_tree::ptree &node, Core::EngineContext *engine_context );

				std::string filename;
				TemplatesManager* templates_manager;
				ConstantsHolder* constants_holder;

		};

	} /* namespace Loader */
} /* namespace UnknownEngine */
