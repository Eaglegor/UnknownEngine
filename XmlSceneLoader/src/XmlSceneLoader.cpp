/*
 * XmlSceneLoader.cpp
 *
 *  Created on: 22 июня 2014 г.
 *      Author: Eaglegor
 */

#include <stdafx.h>

#include <ConstantsHolder.h>
#include <TemplatesManager.h>
#include <SubsystemsLoader.h>
#include <EntitiesLoader.h>

#include <XmlSceneLoader.h>

#include <SupportedTags.h>
#include <EngineContext.h>

namespace UnknownEngine
{
	namespace Loader
	{

		using namespace boost::property_tree;

		XmlSceneLoader::XmlSceneLoader(const std::string &filename) :
				filename(filename),
				templates_manager(nullptr),
				constants_holder(nullptr)
		{
		}

		XmlSceneLoader::~XmlSceneLoader()
		{
			if(constants_holder) delete constants_holder;
			if(templates_manager) delete templates_manager;
		}

		void XmlSceneLoader::loadScene(Core::EngineContext* engine_context, Core::PluginsManager* plugins_manager)
		{
			ptree xml_tree;
			read_xml(filename, xml_tree);

			boost::optional<ptree&> scene_root = xml_tree.get_child_optional(Tags::SCENE);
			if (!scene_root.is_initialized())
			{
				throw InvalidSceneFile("Invalid scene file");
			}

			parseGlobalConstants(scene_root.get());

			boost::optional<ptree&> engine_settings = scene_root.get().get_child_optional(Tags::ENGINE_SECTION);
			if (engine_settings.is_initialized())
			{
				processEngineSettings(engine_settings.get());
			}

			boost::optional<ptree&> subsystems_list = scene_root.get().get_child_optional(Tags::SUBSYSTEMS_SECTION);
			if (subsystems_list.is_initialized())
			{
				processSubsystems(subsystems_list.get(), plugins_manager);
			}

			boost::optional<ptree&> entities_list = scene_root.get().get_child_optional(Tags::ENTITIES_SECTION);
			if (entities_list.is_initialized())
			{
				processEntities(entities_list.get(), engine_context);
			}

		}

		void XmlSceneLoader::processEngineSettings(const boost::property_tree::ptree& node)
		{
			boost::optional<const ptree&> templates_list = node.get_child_optional(Tags::TEMPLATES_SECTION);
			if(templates_list.is_initialized()){
				templates_manager = new TemplatesManager();
				for(const ptree::value_type &iter : templates_list.get()){
					if(iter.first==Tags::TEMPLATE){
						const ptree &attrs = iter.second.get_child(XMLATTR);
						const std::string template_name = attrs.get<std::string>(Attributes::TEMPLATE::NAME);
						const std::string template_filename = attrs.get<std::string>(Attributes::TEMPLATE::FILENAME);
						templates_manager->loadTemplate(template_name, template_filename);
					}
				}
			}
		}

		void XmlSceneLoader::processSubsystems(const boost::property_tree::ptree& node, Core::PluginsManager* plugins_manager)
		{
			SubsystemsLoader subsystems_loader(plugins_manager, this);
			subsystems_loader.loadSubsystems(node);
		}

		void XmlSceneLoader::parseGlobalConstants(const boost::property_tree::ptree& root)
		{
			constants_holder = new ConstantsHolder();
			constants_holder->pushScope();
			for(auto &iter : root){
				if(iter.first==Tags::CONSTANT){
                    constants_holder->parseAndSaveConstant(iter.second);
				}
			}
		}

		void XmlSceneLoader::processEntities(const boost::property_tree::ptree& node, Core::EngineContext* engine_context)
		{
			EntitiesLoader entities_loader(engine_context, this);
			entities_loader.loadEntities(node);
		}

		ConstantsHolder* XmlSceneLoader::getConstantsHolder()
		{
			return constants_holder;
		}

		TemplatesManager* XmlSceneLoader::getTemplatesManager()
		{
			if(templates_manager == nullptr) throw NoTemplatesLoaded("No templates loaded");
			return templates_manager;
		}

	} /* namespace Loader */
} /* namespace UnknownEngine */


